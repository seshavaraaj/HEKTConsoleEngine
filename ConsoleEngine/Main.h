#include <vector>

class IObject;

extern void Debug();

extern void HandleDebug();
extern void HandleQuit();

extern void ObjectInitialization();

extern void SetObjectRenders();

extern void SetObjectAwakes();

extern void SetObjectUpdates(float deltaTime);

extern std::vector<IObject*> IObjects;