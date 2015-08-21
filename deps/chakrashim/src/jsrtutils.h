// Copyright Microsoft. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and / or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#pragma once

#include "jsrt.h"
#include "v8.h"
#include "jsrtproxyutils.h"
#include "jsrtcontextshim.h"
#include "jsrtisolateshim.h"
#include "jsrtcrosscontext.h"

#include "stdint.h"
#include "jsrtstringutils.h"
#include <assert.h>
#include <functional>

#define IfComFailError(v) \
  { \
  hr = (v) ; \
  if (FAILED(hr)) \
    { \
    goto error; \
    } \
  }

#define CHAKRA_UNIMPLEMENTED() jsrt::Unimplemented(__FUNCTION__)
#define CHAKRA_UNIMPLEMENTED_(message) jsrt::Unimplemented(message)

#define CHAKRA_VERIFY(expr) if (!(expr)) { \
  jsrt::Fatal("internal error %s(%d): %s", __FILE__, __LINE__, #expr); }

#ifdef DEBUG
#define CHAKRA_ASSERT(expr) assert(expr)
#else
#define CHAKRA_ASSERT(expr)
#endif

namespace jsrt {

JsErrorCode InitializePromise();

JsErrorCode GetProperty(_In_ JsValueRef ref,
                        _In_ JsValueRef propName,
                        _Out_ JsValueRef *result);

JsErrorCode GetProperty(_In_ JsValueRef ref,
                        _In_ const wchar_t *propertyName,
                        _Out_ JsValueRef *result);

JsErrorCode SetProperty(_In_ JsValueRef ref,
                        _In_ JsValueRef propName,
                        _In_ JsValueRef propValue);

JsErrorCode SetProperty(_In_ JsValueRef ref,
                        _In_ const wchar_t* propName,
                        _In_ JsValueRef propValue);

JsErrorCode DeleteIndexedProperty(_In_ JsValueRef object,
                                  _In_ int index);

JsErrorCode DeleteProperty(_In_ JsValueRef ref,
                           _In_ JsValueRef propName,
                           _Out_ JsValueRef* result);

JsErrorCode GetOwnPropertyDescriptor(_In_ JsValueRef ref,
                                     _In_ JsValueRef prop,
                                     _Out_ JsValueRef* result);

JsErrorCode IsValueInArray(_In_ JsValueRef arrayRef,
                           _In_ JsValueRef valueRef,
                           _Out_ bool* result);

JsErrorCode IsValueInArray(
  _In_ JsValueRef arrayRef,
  _In_ JsValueRef valueRef,
  _In_ std::function<JsErrorCode(JsValueRef, JsValueRef, bool*)> comperator,
  _Out_ bool* result);

JsErrorCode IsCaseInsensitiveStringValueInArray(_In_ JsValueRef arrayRef,
                                                _In_ JsValueRef valueRef,
                                                _Out_ bool* result);

JsErrorCode IsZero(_In_ JsValueRef value,
                   _Out_ bool *result);

JsErrorCode IsUndefined(_In_ JsValueRef value,
                        _Out_ bool *result);

JsErrorCode HasOwnProperty(_In_ JsValueRef object,
                           _In_ JsValueRef prop,
                           _Out_ JsValueRef *result);

JsErrorCode HasProperty(_In_ JsValueRef object,
                        _In_ JsValueRef prop,
                        _Out_ bool *result);

JsErrorCode HasIndexedProperty(_In_ JsValueRef object,
                               _In_ int index,
                               _Out_ bool *result);

JsErrorCode GetEnumerableNamedProperties(_In_ JsValueRef object,
                                         _Out_ JsValueRef *result);

JsErrorCode GetEnumerableIndexedProperties(_In_ JsValueRef object,
                                           _Out_ JsValueRef *result);

JsErrorCode GetIndexedOwnKeys(_In_ JsValueRef object,
                              _Out_ JsValueRef *result);

JsErrorCode GetNamedOwnKeys(_In_ JsValueRef object,
                            _Out_ JsValueRef *result);

JsErrorCode CreateEnumerationIterator(_In_ JsValueRef enumeration,
                                      _Out_ JsValueRef *result);

JsErrorCode CreatePropertyDescriptorsEnumerationIterator(
    _In_ JsValueRef enumeration,
    _Out_ JsValueRef *result);

JsErrorCode ConcatArray(_In_ JsValueRef first,
                        _In_ JsValueRef second,
                        _Out_ JsValueRef *result);

JsErrorCode CallProperty(
  _In_ JsValueRef ref,
  _In_ JsPropertyIdRef idRef,
  _In_reads_(argumentCount) JsValueRef *arguments,
  _In_ unsigned short argumentCount,
  _Out_ JsValueRef *result);

JsErrorCode CallProperty(
  _In_ JsValueRef ref,
  _In_ const wchar_t *propertyName,
  _In_reads_(argumentCount) JsValueRef *arguments,
  _In_ unsigned short argumentCount,
  _Out_ JsValueRef *result);

JsErrorCode GetPropertyOfGlobal(_In_ const wchar_t *propertyName,
                                _Out_ JsValueRef *ref);


JsErrorCode SetPropertyOfGlobal(_In_ const wchar_t *propertyName,
                                _In_ JsValueRef ref);

JsValueRef GetNull();

JsValueRef GetUndefined();

JsValueRef GetTrue();

JsValueRef GetFalse();

// NOT IMPELEMENTED
JsErrorCode SetException(_In_ const wchar_t* message,
                         _In_ const wchar_t* stackTrace);

JsErrorCode GetArrayLength(_In_ JsValueRef arrayRef,
                           _Out_ unsigned int *arraySize);

JsErrorCode InstanceOf(_In_ JsValueRef first,
                       _In_ JsValueRef second,
                       _Out_ bool *result);

JsErrorCode InstanceOfGlobalType(_In_ JsValueRef first,
                                 _In_ const wchar_t* typeName,
                                 _Out_ bool *result);

JsErrorCode CloneObject(_In_ JsValueRef source,
                        _In_ JsValueRef target,
                        _In_ bool cloneProtoype = false);

JsErrorCode ConcatArray(_In_ JsValueRef first,
                        _In_ JsValueRef second,
                        _Out_ JsValueRef *result);

JsErrorCode GetPropertyNames(_In_ JsValueRef object,
                             _Out_ JsValueRef *namesArray);

JsErrorCode AddExternalData(_In_ JsValueRef ref,
                            _In_ JsPropertyIdRef externalDataPropertyId,
                            _In_ void *data,
                            _In_ JsFinalizeCallback onObjectFinalize);

JsErrorCode AddExternalData(_In_ JsValueRef ref,
                            _In_ void *data,
                            _In_ JsFinalizeCallback onObjectFinalize);

JsErrorCode GetExternalData(_In_ JsValueRef ref,
                            _In_ JsPropertyIdRef idRef,
                            _Out_ void **data);

JsErrorCode GetExternalData(_In_ JsValueRef ref,
                            _Out_ void **data);

JsErrorCode CreateFunctionWithExternalData(
    _In_ JsNativeFunction,
    void* data,
    _In_ JsFinalizeCallback onObjectFinalize,
    _Out_ JsValueRef *function);

JsErrorCode ToString(_In_ JsValueRef ref,
                     _Out_ JsValueRef * strRef,
                     _Out_ const wchar_t** str,
                     _In_ bool alreadyString = false);

// the possible values for the property descriptor options
enum PropertyDescriptorOptionValues {
  True,
  False,
  None
};

PropertyDescriptorOptionValues GetPropertyDescriptorOptionValue(bool b);

JsErrorCode CreatePropertyDescriptor(
    _In_ PropertyDescriptorOptionValues writable,
    _In_ PropertyDescriptorOptionValues enumerable,
    _In_ PropertyDescriptorOptionValues configurable,
    _In_ JsValueRef value,
    _In_ JsValueRef getter,
    _In_ JsValueRef setter,
    _Out_ JsValueRef *descriptor);

JsErrorCode CreatePropertyDescriptor(_In_ v8::PropertyAttribute attributes,
                                     _In_ JsValueRef value,
                                     _In_ JsValueRef getter,
                                     _In_ JsValueRef setter,
                                     _Out_ JsValueRef *descriptor);

JsErrorCode DefineProperty(_In_ JsValueRef object,
                           _In_ const wchar_t * propertyName,
                           _In_ PropertyDescriptorOptionValues writable,
                           _In_ PropertyDescriptorOptionValues enumerable,
                           _In_ PropertyDescriptorOptionValues configurable,
                           _In_ JsValueRef value,
                           _In_ JsValueRef getter,
                           _In_ JsValueRef setter);

JsErrorCode DefineProperty(_In_ JsValueRef object,
                           _In_ JsPropertyIdRef propertyIdRef,
                           _In_ PropertyDescriptorOptionValues writable,
                           _In_ PropertyDescriptorOptionValues enumerable,
                           _In_ PropertyDescriptorOptionValues configurable,
                           _In_ JsValueRef value,
                           _In_ JsValueRef getter,
                           _In_ JsValueRef setter);

JsErrorCode GetPropertyIdFromName(_In_ JsValueRef nameRef,
                                  _Out_ JsPropertyIdRef *idRef);

JsErrorCode GetPropertyIdFromValue(_In_ JsValueRef valueRef,
                                   _Out_ JsPropertyIdRef *idRef);

JsErrorCode GetObjectConstructor(_In_ JsValueRef objectRef,
                                 _Out_ JsValueRef *constructorRef);

JsErrorCode SetIndexedProperty(_In_ JsValueRef object,
                               _In_ int index,
                               _In_ JsValueRef value);

JsErrorCode GetIndexedProperty(_In_ JsValueRef object,
                               _In_ int index,
                               _In_ JsValueRef *value);

bool IsOfGlobalType(_In_ JsValueRef objectRef,
                    _In_ const wchar_t *typeName);

void Unimplemented(const char * message);

void Fatal(const char * format, ...);

// Arguments buffer for JsCallFunction
template <int STATIC_COUNT = 4>
class JsArguments {
 private:
  JsValueRef _local[STATIC_COUNT];
  JsValueRef* _args;

 public:
  explicit JsArguments(int count) {
    _args = count <= STATIC_COUNT ? _local : new JsValueRef[count];
  }

  ~JsArguments() {
    if (_args != _local) {
      delete [] _args;
    }
  }

  operator JsValueRef*() {
    return _args;
  }
};

// Check if the errorCode was JsErrorOutOfMemory and if yes,
// create and set the exception on the context
void SetOutOfMemoryErrorIfExist(_In_ JsErrorCode errorCode);

// Clean up internal Chakra state by cleanly disposing at least one
// context
void ExitCleanup();


// Helpers for JsCallFunction/JsConstructObject with undefined as arg0

template <class T>
JsErrorCode CallFunction(const T& api,
                         JsValueRef func,
                         JsValueRef* result) {
  JsValueRef args[] = { jsrt::GetUndefined() };
  return api(func, args, _countof(args), result);
}

template <class T>
JsErrorCode CallFunction(const T& api,
                         JsValueRef func, JsValueRef arg1,
                         JsValueRef* result) {
  JsValueRef args[] = { jsrt::GetUndefined(), arg1 };
  return api(func, args, _countof(args), result);
}

template <class T>
JsErrorCode CallFunction(const T& api,
                         JsValueRef func, JsValueRef arg1, JsValueRef arg2,
                         JsValueRef* result) {
  JsValueRef args[] = { jsrt::GetUndefined(), arg1, arg2 };
  return api(func, args, _countof(args), result);
}

inline JsErrorCode CallFunction(JsValueRef func,
                                JsValueRef* result) {
  return CallFunction(JsCallFunction, func, result);
}

inline JsErrorCode CallFunction(JsValueRef func, JsValueRef arg1,
                                JsValueRef* result) {
  return CallFunction(JsCallFunction, func, arg1, result);
}

inline JsErrorCode CallFunction(JsValueRef func,
                                JsValueRef arg1, JsValueRef arg2,
                                JsValueRef* result) {
  return CallFunction(JsCallFunction, func, arg1, arg2, result);
}

inline JsErrorCode ConstructObject(JsValueRef func,
                                   JsValueRef* result) {
  return CallFunction(JsConstructObject, func, result);
}

inline JsErrorCode ConstructObject(JsValueRef func, JsValueRef arg1,
                                   JsValueRef* result) {
  return CallFunction(JsConstructObject, func, arg1, result);
}

inline JsErrorCode ConstructObject(JsValueRef func,
                                   JsValueRef arg1, JsValueRef arg2,
                                   JsValueRef* result) {
  return CallFunction(JsConstructObject, func, arg1, arg2, result);
}


template <bool LIKELY,
          class JsConvertToValueFunc,
          class JsValueToNativeFunc,
          class T>
JsErrorCode ValueToNative(const JsConvertToValueFunc& JsConvertToValue,
                          const JsValueToNativeFunc& JsValueToNative,
                          JsValueRef value, T* nativeValue) {
  JsErrorCode error;

  // If LIKELY, try JsValueToNative first. Likely to succeed.
  if (LIKELY) {
    error = JsValueToNative(value, nativeValue);
    if (error != JsErrorInvalidArgument) {
      return error;
    }
  }

  // Perform JS conversion first, then to native.
  error = JsConvertToValue(value, &value);
  if (error != JsNoError) {
    return error;
  }
  return JsValueToNative(value, nativeValue);
}

inline JsErrorCode ValueToInt(JsValueRef value, int* intValue) {
  return ValueToNative</*LIKELY*/false>(
    JsConvertValueToNumber, JsNumberToInt, value, intValue);
}

inline JsErrorCode ValueToIntLikely(JsValueRef value, int* intValue) {
  return ValueToNative</*LIKELY*/true>(
    JsConvertValueToNumber, JsNumberToInt, value, intValue);
}

inline JsErrorCode ValueToDouble(JsValueRef value, double* dblValue) {
  return ValueToNative</*LIKELY*/false>(
    JsConvertValueToNumber, JsNumberToDouble, value, dblValue);
}

inline JsErrorCode ValueToDoubleLikely(JsValueRef value, double* dblValue) {
  return ValueToNative</*LIKELY*/true>(
    JsConvertValueToNumber, JsNumberToDouble, value, dblValue);
}

}  // namespace jsrt
