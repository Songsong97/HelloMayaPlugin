#include <maya\MSimple.h>
#include <maya\MGlobal.h>

#define EXPORT _declspec(dllexport)
// define EXPORT for exporting as .dll,
// (Do not need if you use ¡®Maya PluginWizard¡®)
// custom Maya command
class helloMaya : public MPxCommand
{
public:
	virtual MStatus doIt(const MArgList& args)
	{
		MStatus status;
		// <<<your code goes here>>>
		const char *melString =
			"window - title \"Hello Maya\";" \
			"columnLayout - columnAttach \"both\" 50 - rowSpacing 10 - columnWidth 250;" \
			"text - label \"ljl\";" \
			"button - label \"OK\";" \
			"showWindow;";
		MGlobal::executeCommand(melString);
		return status;
	}
	static void *creator() { return new helloMaya; }
};

// Initialize Plugin upon loading
EXPORT MStatus initializePlugin(MObject obj)
{
	MStatus stat;
	MFnPlugin plugin(obj, "CIS660", "1.0", "Any");
	stat = plugin.registerCommand("helloMaya", helloMaya::creator);
	if (!stat) stat.perror("registerCommand failed");
	return stat;
}

// Cleanup Plugin upon unloading
EXPORT MStatus uninitializePlugin(MObject obj)
{
	MStatus stat;
	MFnPlugin plugin(obj);
	stat = plugin.deregisterCommand("helloMaya");
	if (!stat) stat.perror("deregisterCommand failed");
	return stat;
}
