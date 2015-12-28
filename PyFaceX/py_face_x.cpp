#include "py_face_x.h"


static PyObject* facex_echo(PyObject* self, PyObject* args)
{
	char* s;

	if (!PyArg_ParseTuple(args, "s", &s))
		return NULL;

	return Py_BuildValue("s", s);
}



//std::vector<cv::Point2d> Alignment(cv::Mat image, cv::Rect face_rect)

static PyObject* facex_align(PyObject* self, PyObject* args)
{
	cv::Mat image;
	cv::Rect face_rect;
	FaceX* fx = new FaceX("");
	std::vector<cv::Point2d> landmarks = fx->Alignment(image, face_rect);

	return Py_BuildValue("O", landmarks);
}

static PyMethodDef facexMethods[] =
{
	{ "echo", facex_echo, METH_VARARGS, "Echo for test." },
	{ "align", facex_align, METH_VARARGS, "Do face alignment." },
	{ NULL, NULL, 0, NULL }
};

static struct PyModuleDef moduledef =
{
	PyModuleDef_HEAD_INIT,
	"facex",						/* m_name */
	"Python module of FaceX",		/* m_doc */
	-1,								/* m_size */
	facexMethods,					/* m_methods */
	NULL,							/* m_reload */
	NULL,							/* m_traverse */
	NULL,							/* m_clear */
	NULL,							/* m_free */
};

PyMODINIT_FUNC
PyInit_facex(void)
{
#if PY_MAJOR_VERSION >= 3
	return PyModule_Create(&moduledef);
#else
	return Py_InitModule("facex", facexMethods);
#endif
}