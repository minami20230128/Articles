# ・「実践Django」まとめ  
## 1章
HttpRequestクラスはビュー関数を直接呼び出すため、ビュー関数の単体テスト用。
```
from django.http import HttpRequest
request = HttpRequest()
response = top(request)
```
Clientクラスはエンドポイントにリクエストを送るため、結合テスト・E2Eテスト用。
```
from django.test import Client
client = Client()
response = client.get("/")
```

## 2章
- モデルがどのようなSQLでマイグレーションされるかは、以下のコマンドで確認可能。
```
manage.py sqlmigrate <app_label> <migration_name>
```
- 「id」カラムはモデルになくても勝手にオートインクリメントの項目として追加される。  
- テーブル名を変更したい場合Metaオプションでできる。 
- オブジェクトの操作は以下のように行う。  
保存...オブジェクト.save()  
消去...オブジェクト.delete()  
更新...フィールドを変更したうえでオブジェクト.save()  
- DBのテーブル操作は以下のように行う。
全件取得...テーブル名.objects.all()  
idで取得...テーブル名.filter(id)  
特定のid以外の全件を取得...テーブル名.exclude(id)  
- オリジナルのクエリパターンを作成する場合、django.db.models.Managerを継承したモデルマネージャを作成。  
- トランザクション管理したい場合、以下のように書く。
```
with transaction.atomic():
    ...
```
### N+1問題への対処
N+1問題...DBアクセスにおいて、1件のSQLで取得できる情報を複数件のSQLで取得しようとしてしまうこと。  
ORMにおいて、DB上ではそれぞれ別テーブルに記録されているオブジェクトとそのメンバ変数を取り出したときに起きやすい。  
Djangoでこれを防ぐには2つの方法がある。  

- select_related
  外部キーや一対一の関係性に使う。
  テーブルを事前に連結してから取り出す。
```
テーブル名.objects().select_related(JOINするカラム名).all()
```

- prefetch_related
  一対多、多対多の関係性に使う。
  Pythonコード上でテーブル連結する。
```
テーブル名.objects.prefetch_related(JOINするカラム名)
```

## 8章
serializers.pyに、クラスをどのようにJSONに変更するかを書く。
serializer.ModelSerializerを継承させる。
```
from rest_framework import serializers
from .models import Task

class TaskSerializer(serializers.ModelSerializer):
    class Meta:
        model = Task
        fields = ['id', 'title', 'start_date', 'due_date', 'status']

class TaskInputSerializer(serializers.Serializer):
    title = serializers.CharField()
    start_date = serializers.DateTimeField()
    due_date = serializers.DateTimeField()
    condition = serializers.CharField(required=False, allow_blank=True)
    memo = serializers.CharField(required=False, allow_blank=True)
    status = serializers.CharField(required=False, allow_blank=True)

class StatusInputSerializer(serializers.Serializer):
    status = serializers.CharField()
```

views.pyにエンドポイントを定義する。

```
# views.py
from rest_framework import status, viewsets
from rest_framework.decorators import action
from rest_framework.response import Response
from django.utils.timezone import now
from .models import Task
from .serializers import TaskSerializer, TaskInputSerializer, StatusInputSerializer

class TaskViewSet(viewsets.ViewSet):

    def list(self, request):
        tasks = Task.objects.all()
        serializer = TaskSerializer(tasks, many=True)
        return Response(serializer.data)

    @action(detail=False, methods=['post'], url_path='new')
    def create_task(self, request):
        serializer = TaskInputSerializer(data=request.data)
        serializer.is_valid(raise_exception=True)
        task = Task(**serializer.validated_data)
        task.created_at = now()
        task.save()
        return Response(status=status.HTTP_200_OK)

    def retrieve(self, request, pk=None):
        try:
            task = Task.objects.get(pk=pk)
        except Task.DoesNotExist:
            return Response(status=status.HTTP_404_NOT_FOUND)
        serializer = TaskSerializer(task)
        return Response(serializer.data)

    def update(self, request, pk=None):
        serializer = TaskInputSerializer(data=request.data)
        serializer.is_valid(raise_exception=True)
        try:
            task = Task.objects.get(pk=pk)
        except Task.DoesNotExist:
            return Response(status=status.HTTP_404_NOT_FOUND)
        for attr, value in serializer.validated_data.items():
            setattr(task, attr, value)
        task.updated_at = now()
        task.save()
        return Response(status=status.HTTP_200_OK)

    @action(detail=True, methods=['patch'], url_path='status')
    def update_status(self, request, pk=None):
        serializer = StatusInputSerializer(data=request.data)
        serializer.is_valid(raise_exception=True)
        try:
            task = Task.objects.get(pk=pk)
        except Task.DoesNotExist:
            return Response(status=status.HTTP_404_NOT_FOUND)
        task.status = serializer.validated_data['status']
        task.save()
        return Response(status=status.HTTP_200_OK)

```
urls.pyにURLのマッピング方法を書く。
```
from rest_framework.routers import DefaultRouter
from .views import TaskViewSet

router = DefaultRouter()
router.register(r'tasks', TaskViewSet, basename='task')

urlpatterns = router.urls
```
これを書くだけで、以下のルートが自動生成される。
```
| HTTPメソッド | URLパターン      | アクション           |
| -------- | ------------ | --------------- |
| GET      | /tasks/      | list            |
| POST     | /tasks/      | create          |
| GET      | /tasks/{pk}/ | retrieve        |
| PUT      | /tasks/{pk}/ | update          |
| PATCH    | /tasks/{pk}/ | partial\_update |
| DELETE   | /tasks/{pk}/ | destroy         |

```