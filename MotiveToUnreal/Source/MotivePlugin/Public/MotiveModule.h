// Some copyright should be here...

#pragma once

#include "ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(MotiveLog, Log, All);

class FMotiveModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

protected:
	/** Convenience function*/
	bool SearchForDllPath(const FString _searchBase, const FString _dllName);

};