 import cv2
 import numpy as np
 from skimage.measure import compare_ssim
  
 #константа процент совпадения между кадрами
 DIFF = 0.85
  
 def main():
     cap = cv2.VideoCapture(0)
     fourcc = cv2.VideoWriter_fourcc(*'MJPG')
     out = cv2.VideoWriter('output.avi', fourcc, 20.0, (int(cap.get(3)), int(cap.get(4))))
     #считываем первый кадр
     _, frame1 = cap.read()
     while True:
         #считываем второй кадр
         _, frame2 = cap.read()
         # конвертируем в серый
         frame1_gray = cv2.cvtColor(frame1, cv2.COLOR_BGR2GRAY)
         frame2_gray = cv2.cvtColor(frame2, cv2.COLOR_BGR2GRAY)
  
         # рассчитываем различие
         (score, _) = compare_ssim(frame1_gray, frame2_gray, full=True)
  
         # считывем 1 кадр
         frame1 = frame2
  
         #если различий больше чем DIFF
         if score < DIFF:
             out.write(frame2)
  
         cv2.imshow('frame', frame2)
  
         key = cv2.waitKey(1)
         if key == 27:
             cap.release()
             out.release()
             break
  
     cv2.destroyAllWindows()
  
  
  
 if __name__ == '__main__':
     main()
