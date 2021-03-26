#pragma once

#ifdef _MSC_VER
#define __CLASS_FUNCTION__ __FUNCTION__
#endif

#ifdef __GNUG__ 
#include <cxxabi.h>
#include <execinfo.h>
char *class_func(const char *c, const char *f)
{
	int status;
	static char buff[100];
	char *demangled = abi::__cxa_demangle(c, NULL, NULL, &status);
	snprintf(buff, sizeof(buff), "%s::%s", demangled, f);
	free(demangled);
	return buff;
}
#define __CLASS_FUNCTION__ class_func(typeid(*this).name(), __func__) 
#endif

/* ClassName::FunctionName where this is called. */
#define CURRENT_CLASS_FUNCTION (FString(__CLASS_FUNCTION__))
/* Class Name where this is called. */
#define CURRENT_CLASS (FString(__CLASS_FUNCTION__).Left(FString(__CLASS_FUNCTION__).Find(TEXT(":"))) )
/* Function Name where this is called. */
#define CURRENT_FUNCTION (FString(__CLASS_FUNCTION__).Right(FString(__CLASS_FUNCTION__).Len() - FString(__CLASS_FUNCTION__).Find(TEXT("::")) - 2 ))
/* Line Number where this is called. */
#define CURRENT_LINE  (FString::FromInt(__LINE__))
/* Class Name and Line Number where this is called. */
#define CURRENT_CLASS_LINE (CURRENT_CLASS + " (" + CURRENT_LINE + ")")
/* Class Name and Function Name and Line Number where this is called. */
#define CURRENT_CLASS_FUNCTION_LINE (CURRENT_CLASS_FUNCTION + " (" + CURRENT_LINE + ")")
/* Function Signature where this is called. */
#define CURRENT_FUNCTIONSIG (FString(__FUNCSIG__))

/*
 * UE_LOG macros
 */

/* Equivalent to UE_LOG. */
#define LOG_UE(CategoryName, Verbosity, Message, ...) UE_LOG(CategoryName, Verbosity, Message, ##__VA_ARGS__)
/* Log macro. Style: ClassName::FunctionName Format. */
#define LOG_SENDER(CategoryName, Verbosity, Message, ...) UE_LOG(CategoryName, Verbosity, TEXT("%s "), TEXT(__CLASS_FUNCTION__), Message, ##__VA_ARGS__ )

/* Log macro. Style: ClassName::FunctionName (Line) Message. */
#define LOG(CategoryName, Message) UE_LOG(CategoryName, Log, TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString(Message))
/* Log macro. Style: ClassName::FunctionName (Line) Message. */
#define LOG_PRINTF(CategoryName, FormatString , ...) UE_LOG(CategoryName, Log, TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )

/* Log macro with verbosity. Style: ClassName::FunctionName (Line) Message. */
#define LOG_VERBOSITY(CategoryName, Verbosity, Message) UE_LOG(CategoryName, Verbosity, TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString(Message))
/* Log macro with verbosity. Style: ClassName::FunctionName (Line) Message. */
#define LOG_VERBOSITY_PRINTF(CategoryName, Verbosity, FormatString , ...) UE_LOG(CategoryName, Verbosity, TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )

/* Log warning macro. Style: ClassName::FunctionName (Line) Message. */
#define LOG_WARNING(CategoryName, Message) UE_LOG(CategoryName, Warning, TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString(Message))
/* Log warning macro. Style: ClassName::FunctionName (Line) Message. */
#define LOG_WARNING_PRINTF(CategoryName, FormatString , ...) UE_LOG(CategoryName, Warning, TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )

/* Log error macro. Style: ClassName::FunctionName (Line) Message. */
#define LOG_ERROR(CategoryName, Message) UE_LOG(CategoryName, Error, TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString(Message))
/* Log error macro. Style: ClassName::FunctionName (Line) Message. */
#define LOG_ERROR_PRINTF(CategoryName, FormatString , ...) UE_LOG(CategoryName, Error, TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )
#define LOG_ERROR_Format(CategoryName, FormatString , ...) UE_LOG(CategoryName, Error, TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )

/* Log fatal macro. Style: ClassName::FunctionName (Line) Message. */
#define LOG_FATAL(CategoryName, Message) UE_LOG(CategoryName, Fatal, TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString(Message))
/* Log fatal macro. Style: ClassName::FunctionName (Line) Message. */
#define LOG_FATAL_PRINTF(CategoryName, FormatString , ...) UE_LOG(CategoryName,Fatal,TEXT("%s: %s"), *CURRENT_CLASS_FUNCTION_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )

/*
 * Screen Messages macros
 */

#define LOG_SCREENMSG(Message) (GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *(CURRENT_CLASS_FUNCTION_LINE + ": " + Message)) )
#define LOG_SCREENMSG_PRINTF(FormatString , ...) (GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, *(CURRENT_CLASS_FUNCTION_LINE + ": " + (FString::Printf(TEXT(FormatString), ##__VA_ARGS__ )))) )
