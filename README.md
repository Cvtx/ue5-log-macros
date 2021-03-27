# ue4-log-macros
A single header file with useful macros for logging in Unreal Engine 4 projects.
These macros expand usage of standart UE_LOG macro.
Macros with _PRINTF suffix can have formatted text (see example), without - just const strings.

Usage example:

```cpp
#pragma once

#include "CoreMinimal.h"
#include "LogMacros.h"

#include "MyClass.generated.h"

UCLASS()
class UMyClass : public UObject
{

  GENERATED_BODY()
   
public:

  void Log()
  {
  
    /* Simple log */
    LOG(LogTemp, "Log from my function.");
    
    /* Formatted log */
    LOG_PRINTF(LogTemp, "Log with format: %s %d ", TEXT("some text"), 123);
    
    /* Log with desired verbosity */
    LOG_VERBOSITY(LogTemp, Warning, "Custom verbosity.");
    
    /* Log warning (don't have to specify verbosity) */
    LOG_WARNING(LogTemp, "Some warning.");
    
    /* Log error (don't have to specify verbosity) */
    LOG_ERROR(LogTemp, "Some error.")
  }
  
};
```

Calling UMyClass::Log function will print this:

```cpp
LogTemp: UMyClass::Log (19): Log from my function.
LogTemp: UMyClass::Log (22): Log with format: some text 123
LogTemp: Warning: UMyClass::Log (25): Custom verbosity.
LogTemp: Warning: UMyClass::Log (28): Some warning.
LogTemp: Error: UMyClass::Log (31): Some error.
```

File also contains additional macros to help build your own custom log macros.

##### Note that this file use preprocessor macros, which some of them can be compiler-specific. If you building for platform, other than Windows, or building for multiple platforms, you should call compiler-specific macros. There is also a basic example on how to call compiler-specific macros with #ifdef directive. See documentation page for [MSVC](https://docs.microsoft.com/ru-ru/cpp/preprocessor/predefined-macros).
