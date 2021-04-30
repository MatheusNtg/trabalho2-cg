"""
Hand Tracing Module
By: Murtaza Hassan
Youtube: http://www.youtube.com/c/MurtazasWorkshopRoboticsandAI
Website: https://www.murtazahassan.com/

Alterado e adaptado por: Matheus da Silva Rodrigues
"""

import cv2
import time
import numpy as np
import HandTrackingModule as htm
import math

from subprocess import call


################################
wCam, hCam = 640, 480
################################

# Captura de vídeo
cap = cv2.VideoCapture(0)
cap.set(3, wCam)
cap.set(4, hCam)
pTime = 0


# 1 Line-out
# 3 HDMI

DEVICE = 1

detector = htm.handDetector(detectionCon=0.85)

while True:
    success, img = cap.read()
    # Identifica as mãos na imagem
    img = detector.findHands(img)
    # Identifica a posição das mãos
    lmList = detector.findPosition(img, draw=False)

    if len(lmList) != 0:

        # Obtem as coordenadas do dedo indicador e do polegar
        x1, y1 = lmList[4][1], lmList[4][2]
        x2, y2 = lmList[8][1], lmList[8][2]
        cx, cy = (x1 + x2) // 2, (y1 + y2) // 2

        # Cria círculos em volta da mão
        cv2.circle(img, (x1, y1), 15, (255, 0, 255), cv2.FILLED)
        cv2.circle(img, (x2, y2), 15, (255, 0, 255), cv2.FILLED)
        cv2.circle(img, (cx, cy), 15, (255, 0, 255), cv2.FILLED)

        # Cria uma linha entre o indicador e o polegar
        cv2.line(img, (x1, y1), (x2, y2), (255, 0, 255), 3)

        # Calcula a distância entre o polegar e o indicador
        length = math.hypot(x2 - x1, y2 - y1)

        # normalized_value = (length-min(length))/(max(length)-min(length))

        # Normaliza o valor
        normalized_value = (length - 10) / (220 - 10)

        # Seta o valor do volume
        call(['pactl', 'set-sink-volume', str(DEVICE), f'{str(math.floor(normalized_value*100))}%'])

        # Caso o valor seja pequeno identificamos como mudo
        if length < 50:
            cv2.circle(img, (cx, cy), 15, (0, 255, 0), cv2.FILLED)

    # Calcula o FPS
    cTime = time.time()
    fps = 1 / (cTime - pTime)
    pTime = cTime

    # Mostra o FPS
    cv2.putText(img, f'FPS: {int(fps)}', (40, 50), cv2.FONT_HERSHEY_COMPLEX,
                1, (255, 0, 0), 3)

    cv2.imshow("Img", img)
    cv2.waitKey(1)
