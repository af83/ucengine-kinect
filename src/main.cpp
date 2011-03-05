// Headers for OpenNI
#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include <XnHash.h>
#include <XnLog.h>

// Header for NITE
#include <XnVNite.h>
#include <XnVCircleDetector.h>
#include <XnVSwipeDetector.h>
#include <XnVWaveDetector.h>

// local header
#include "PointDrawer.h"

#define CHECK_RC(rc, what)											\
	if (rc != XN_STATUS_OK)											\
	{																\
		printf("%s failed: %s\n", what, xnGetStatusString(rc));		\
		return rc;													\
	}

#include <GL/glut.h>

// OpenNI objects
xn::Context g_Context;
xn::DepthGenerator g_DepthGenerator;
xn::HandsGenerator g_HandsGenerator;

// NITE objects
XnVSessionManager* g_pSessionManager;
XnVFlowRouter* g_pFlowRouter;

// the drawer
XnVPointDrawer* g_pDrawer;

#define GL_WIN_SIZE_X 720
#define GL_WIN_SIZE_Y 480

// Draw the depth map?
XnBool g_bDrawDepthMap = true;
XnBool g_bPrintFrameID = false;
// Use smoothing?
XnFloat g_fSmoothing = 0.0f;
XnBool g_bQuit = false;

SessionState g_SessionState = NOT_IN_SESSION;

void CleanupExit()
{
	g_Context.Shutdown();
	exit (1);
}

void XN_CALLBACK_TYPE SessionStarting(const XnPoint3D& ptPosition, void* UserCxt)
{
	fprintf(stderr, "Session start: (%f,%f,%f)\n", ptPosition.X, ptPosition.Y, ptPosition.Z);
	g_SessionState = IN_SESSION;
}
void XN_CALLBACK_TYPE SessionEnding(void* UserCxt)
{
	fprintf(stderr, "Session end\n");
	g_SessionState = NOT_IN_SESSION;
}
void XN_CALLBACK_TYPE NoHands(void* UserCxt)
{
	fprintf(stderr, "Quick refocus\n");
	g_SessionState = QUICK_REFOCUS;
}
void XN_CALLBACK_TYPE OnCircleCB(XnFloat fTimes, XnBool bConfident, const XnVCircle* pCircle, void* pUserCxt)
{
	fprintf(stderr, "Circle %f\n", fTimes);
}
void XN_CALLBACK_TYPE OnNoCircleCB(XnFloat fLastValue, XnVCircleDetector::XnVNoCircleReason eReason, void* pUserCxt)
{
	printf("NoCircle %f\n", fLastValue);
}
void XN_CALLBACK_TYPE OnSwipeUpCB(XnFloat fVelocity, XnFloat fAngle, void* pUserCxt)
{
	printf("SwipeUp\n");
}
void XN_CALLBACK_TYPE OnSwipeDownCB(XnFloat fVelocity, XnFloat fAngle, void* pUserCxt)
{
	printf("SwipeDown\n");
}
void XN_CALLBACK_TYPE OnSwipeLeftCB(XnFloat fVelocity, XnFloat fAngle, void* pUserCxt)
{
	printf("SwipeLeft\n");
}
void XN_CALLBACK_TYPE OnSwipeRightCB(XnFloat fVelocity, XnFloat fAngle, void* pUserCxt)
{
	printf("SwipeRight\n");
}
void XN_CALLBACK_TYPE OnWaveCB(void* cxt)
{
	printf("Wave\n");
}


// this function is called each frame
void glutDisplay (void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	XnMapOutputMode mode;
	g_DepthGenerator.GetMapOutputMode(mode);
	glOrtho(0, mode.nXRes, mode.nYRes, 0, -1.0, 1.0);
	glDisable(GL_TEXTURE_2D);
	g_Context.WaitAndUpdateAll();
	g_pSessionManager->Update(&g_Context);
	PrintSessionState(g_SessionState);
	glutSwapBuffers();
}

void glutIdle (void)
{
	if (g_bQuit) { CleanupExit(); }
	glutPostRedisplay();
}

void glutKeyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		// Exit
		CleanupExit();
	case 'd':
		// Toggle drawing of the depth map
		g_bDrawDepthMap = !g_bDrawDepthMap;
		g_pDrawer->SetDepthMap(g_bDrawDepthMap);
		break;
	case 'f':
		g_bPrintFrameID = !g_bPrintFrameID;
		g_pDrawer->SetFrameID(g_bPrintFrameID);
		break;
	case 's':
		// Toggle smoothing
		if (g_fSmoothing == 0)
			g_fSmoothing = 0.1;
		else
			g_fSmoothing = 0;
		g_HandsGenerator.SetSmoothing(g_fSmoothing);
		break;
	case 'e':
		// end current session
		g_pSessionManager->EndSession();
		break;
	}
}

void glInit (int * pargc, char ** argv)
{
	glutInit(pargc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
	glutCreateWindow ("PrimeSense Nite Point Viewer");
	//glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
	glutKeyboardFunc(glutKeyboard);
	glutDisplayFunc(glutDisplay);
	glutIdleFunc(glutIdle);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

// xml to initialize OpenNI
#define SAMPLE_XML_PATH "data/Tracking.xml"

int main(int argc, char ** argv)
{
	XnStatus rc = XN_STATUS_OK;

	// Initialize OpenNI
	rc = g_Context.InitFromXmlFile(SAMPLE_XML_PATH);
	CHECK_RC(rc, "InitFromXmlFile");

	rc = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
	CHECK_RC(rc, "Find depth generator");
	rc = g_Context.FindExistingNode(XN_NODE_TYPE_HANDS, g_HandsGenerator);
	CHECK_RC(rc, "Find hands generator");

	// Create NITE objects
	g_pSessionManager = new XnVSessionManager;
	rc = g_pSessionManager->Initialize(&g_Context, "Click,Wave", "RaiseHand");
	CHECK_RC(rc, "SessionManager::Initialize");

	g_pSessionManager->RegisterSession(NULL, SessionStarting, SessionEnding, NULL);

	g_pDrawer = new XnVPointDrawer(20, g_DepthGenerator);
	g_pFlowRouter = new XnVFlowRouter;
	g_pFlowRouter->SetActive(g_pDrawer);
	g_pSessionManager->AddListener(g_pFlowRouter);

	g_pDrawer->RegisterNoPoints(NULL, NoHands);
	g_pDrawer->SetDepthMap(g_bDrawDepthMap);

	// init & register circle control
	XnVCircleDetector circle;
	circle.RegisterCircle(NULL, OnCircleCB);
	circle.RegisterNoCircle(NULL, OnNoCircleCB);
	g_pSessionManager->AddListener(&circle);

	// init & register swipe control
	XnVSwipeDetector swipe;
	swipe.RegisterSwipeUp(NULL, OnSwipeUpCB);
	swipe.RegisterSwipeDown(NULL, OnSwipeDownCB);
	swipe.RegisterSwipeLeft(NULL, OnSwipeLeftCB);
	swipe.RegisterSwipeRight(NULL, OnSwipeRightCB);
	g_pSessionManager->AddListener(&swipe);

	// init & register wave control
	XnVWaveDetector wave;
	wave.RegisterWave(NULL, OnWaveCB);
	g_pSessionManager->AddListener(&wave);

	// Initialization done. Start generating
	rc = g_Context.StartGeneratingAll();
	CHECK_RC(rc, "StartGenerating");

	// Mainloop
	glInit(&argc, argv);
	glutMainLoop();
}
