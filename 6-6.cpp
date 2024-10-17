#include <GL/freeglut.h>

static int Day = 0, Time = 0;

//�� ��ġ, ǥ��
static float starX = 0.0f, starZ = 0.0f;
bool starVisible = true;
//���� ��ġ ������
void GenerateRandomStarPosition() {
	starX = (rand() % 200 - 100) / 100.0f;
	starZ = (rand() % 200 - 100) / 100.0f;
}

//� ũ��, �ӵ�, ǥ��
float meteorSize = 0.05f;
float meteorX = 0.0f, meteorZ = 1.0f;
float meteorSpeed = 0.01f;
bool meteorVisible = true;

// � �ʱ�ȭ
void ResetMeteor() {
	meteorVisible = true;
	meteorSize = 0.05f;
	meteorZ = 1.0f;
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//����
	gluLookAt(0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
	//�¾�
	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16);
	//��
	if (starVisible) {
		glPushMatrix();
			glTranslatef(starX, 0.0, starZ);
			glColor3f(1.0, 1.0, 0.0);
			glutSolidSphere(0.01, 10, 8);
		glPopMatrix();
	}
	//����
	glPushMatrix();
		glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
		glTranslatef(0.7, 0.0, 0.0);
		glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
		glColor3f(0.5, 0.6, 0.7);
		glutWireSphere(0.1, 10, 8);
		//��
		glPushMatrix();
			glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
			glTranslatef(0.2, 0.0, 0.0);
			glColor3f(0.9, 0.8, 0.2);
			glutWireSphere(0.04, 10, 8);
		glPopMatrix();
		//�
		if (meteorVisible && meteorSize > 0.0f) {
			glPushMatrix();
				glTranslatef(meteorX, 0.0, meteorZ);
				glColor3f(0.3, 0.3, 0.3);
				glutSolidSphere(meteorSize, 10, 8);
			glPopMatrix();
			meteorZ -= meteorSpeed;
			meteorSize -= 0.0005f;
			if (meteorZ <= 0.1f) {
				ResetMeteor();
			}
		}
		//���ּ�
		glPushMatrix();
			glRotatef((GLfloat)Day, 0.0, 0.5, 0.0);
			glTranslatef(0.13, 0.0, 0.0);
			glRotatef(45, 0.0, 1.0, 0.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCone(0.01, 0.02, 10, 8);
			glTranslatef(0.2, 0.0, 0.0);
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		Day = (Day + 10) % 360;
		//�� ��ġ
		if (Day % 90 == 0) {
			starVisible = false;
		}
		else if (Day % 90 == 10) {
			GenerateRandomStarPosition();
			starVisible = true;
		}
		//
		glutPostRedisplay();
		break;
	case 't':
		Time = (Time + 5) % 360;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();
	return 0;
}