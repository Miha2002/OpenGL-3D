# OpenGL - FlappyBird, but 3D
### Not fully functional

Am încercat să recreăm scena cu Flappy Bird din 2D în 3D. Pasărea noastră se poate deplasa pe sus/jos și stânga/dreapta, iar observatorul se poate plimba prin scenă folosind WASD pentru mișcare și Q,E pentru direcție.
Am implementat ceață pentru a face scena mai interesantă și pentru a amplifica distanța față de clădirile din fundal.

Alte aspecte punctuale:
- Am iluminat scena folosind nuanțe de roșu și albastru, lumina ambient și diffuse este mov.
- Am creat funcția init(void) și am folosit GL_FOG pentru a adăuga ceață. Pentru a nu afecta culorile atât de mult, am setat densitatea < 0.1. Culoarea ceții este gri-albastru.
- Am adăugat mișcarea în stânga/dreapta (strafing) a observatorului.
- Pasărea poate fi mișcată, însă nu am implementat un sistem de coliziune cu celelalte obiecte, așa că poate trece prin țevile din jur.
