#include <Python.h>

#include <Windows.h>
#include <tchar.h>

#include "RzChromaSDKDefines.h"
#include "RzChromaSDKTypes.h"
#include "RzErrors.h"

typedef RZRESULT (*INIT)(void);
typedef RZRESULT (*CREATEKEYBOARDEFFECT)(ChromaSDK::Keyboard::EFFECT_TYPE Effect, PRZPARAM pParam, RZEFFECTID *pEffectId);
typedef RZRESULT (*SETEFFECT)(RZEFFECTID EffectId);

HMODULE chromaSDKModule;
INIT Init;
CREATEKEYBOARDEFFECT CreateKeyboardEffect;
SETEFFECT SetEffect;

#define RANDOM_BYTE()		(rand() % 255)
#define NORMAL_COLOR    RGB(0, 82, 82)
#define INSERT_COLOR    RGB(120, 159, 0)
#define VISUAL_COLOR    RGB(120, 159, 0)

void
fill_effect_with_color(ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE &Effect, COLORREF color) {
	for (UINT row = 0; row < ChromaSDK::Keyboard::MAX_ROW; row++) {
		for (UINT col = 0; col < ChromaSDK::Keyboard::MAX_COLUMN; col++) {
			Effect.Color[row][col] = color;
		}
	}
}

static PyObject *
chroma_insertmode(PyObject *self, PyObject *args) {
	ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};
  fill_effect_with_color(Effect, INSERT_COLOR);
	Effect.Color[HIBYTE(ChromaSDK::Keyboard::RZKEY_ESC)][LOBYTE(ChromaSDK::Keyboard::RZKEY_ESC)] = NORMAL_COLOR;

  RZRESULT effectResult = CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, NULL);

  Py_RETURN_NONE;
}

static PyObject *
chroma_normalmode(PyObject *self, PyObject *args) {
	ChromaSDK::Keyboard::CUSTOM_EFFECT_TYPE Effect = {};
  fill_effect_with_color(Effect, NORMAL_COLOR);
	Effect.Color[HIBYTE(ChromaSDK::Keyboard::RZKEY_I)][LOBYTE(ChromaSDK::Keyboard::RZKEY_I)] = INSERT_COLOR;

  RZRESULT effectResult = CreateKeyboardEffect(ChromaSDK::Keyboard::CHROMA_CUSTOM, &Effect, NULL);

  Py_RETURN_NONE;
}

static PyMethodDef ChromaMethods[] = {
		{ "insertmode", chroma_insertmode, METH_VARARGS,
		"Switch the keyboard to insert mode." },

		{ "normalmode", chroma_normalmode, METH_VARARGS,
		"Switch the keyboard to normal mode." },

		{ NULL, NULL, 0, NULL }
};

static struct PyModuleDef chromamodule = {
	PyModuleDef_HEAD_INIT,
	"chroma",
	NULL,
	-1,
	ChromaMethods
};

PyMODINIT_FUNC
PyInit_chroma(void)
{
  // Load the chroma SDK and get the address of needed functions
	chromaSDKModule = LoadLibrary(_T("RzChromaSDK.dll"));
	Init = (INIT)GetProcAddress(chromaSDKModule, "Init");
	CreateKeyboardEffect = (CREATEKEYBOARDEFFECT)GetProcAddress(chromaSDKModule, "CreateKeyboardEffect");
	SetEffect = (SETEFFECT)GetProcAddress(chromaSDKModule, "SetEffect");

	// Initialize the driver
	Init();

	return PyModule_Create(&chromamodule);
}
