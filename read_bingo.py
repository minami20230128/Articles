import cv2

# 画像を読み込む
image = cv2.imread('bingo_card.jpg')

# グレースケールに変換
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# ガウスぼかしを適用してノイズを除去
blurred = cv2.GaussianBlur(gray, (5, 5), 0)

# Canny エッジ検出
edges = cv2.Canny(blurred, 50, 150)

# 輪郭検出
contours, _ = cv2.findContours(edges, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

squares = []

# 四角形の検出
for contour in contours:
    # 輪郭を近似して多角形にする
    epsilon = 0.02 * cv2.arcLength(contour, True)
    approx = cv2.approxPolyDP(contour, epsilon, True)
    
    # 四角形の検出（近似された多角形が4つの頂点を持つか確認）
    if len(approx) == 4:
        # 四角形を描画する
        squares = []
        cv2.drawContours(image, [approx], -1, (0, 255, 0), 2)

selected_squares = []
current_rect = None
drawing = False

cv2.imshow('Detected Squares', image)

def mouse_callback(event, x, y, flags, param):
    global start_point, drawing, squares, image, original_image

    if event == cv2.EVENT_LBUTTONDOWN:
        if not drawing:
            # 四角形の描画開始
            start_point = (x, y)
            drawing = True
        else:
            # 四角形の描画終了
            end_point = (x, y)
            drawing = False
            squares.append((start_point, end_point))
            # 四角形を描画する
            cv2.rectangle(image, start_point, end_point, (0, 255, 0), 2)
            cv2.imshow('Image', image)
    
    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing:
            # 描画中の矩形をリアルタイムで表示
            temp_image = original_image.copy()
            cv2.rectangle(temp_image, start_point, (x, y), (0, 255, 0), 2)
            cv2.imshow('Image', temp_image)
    
    elif event == cv2.EVENT_LBUTTONDBLCLK:
        # ダブルクリックで四角形を消去
        for (rect_start, rect_end) in squares:
            if (rect_start[0] <= x <= rect_end[0] and
                rect_start[1] <= y <= rect_end[1]):
                squares.remove((rect_start, rect_end))
                # 再描画
                image = original_image.copy()
                for (start, end) in squares:
                    cv2.rectangle(image, start, end, (0, 255, 0), 2)
                cv2.imshow('Image', image)


# マウスコールバック関数を設定
cv2.setMouseCallback('Detected Squares', mouse_callback)

# ユーザーの操作を待つ
cv2.waitKey(0)
cv2.destroyAllWindows()
