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

		// Parse the arguments
		MString name("");
		int id = 0;
		for (int i = 0; i < args.length(); i++) {
			if (MString("-name") == args.asString(i, &status) && MS::kSuccess == status) {
				MString tmp = args.asString(++i, &status);
				if (MS::kSuccess == status) {
					name = tmp;
				}
			}
			else if (MString("-i") == args.asString(i, &status) && MS::kSuccess == status) {
				int tmp = args.asInt(++i, &status);
				if (MS::kSuccess == status) {
					id = tmp;
				}
			}
		}

		// Construct the dialog window
		MString melString =
			"window -title \"Hello Maya\";" \
			"columnLayout -columnAttach \"both\" 50 -rowSpacing 10 -columnWidth 250;" \
			"text -label \"Name:";
		melString += name;
		melString += "\";";
		melString += "text -label \"ID:";
		melString += id;
		melString += "\";";
		melString +=
			"button -label \"OK\";" \
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
