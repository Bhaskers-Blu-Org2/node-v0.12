// Copyright 2014 the V8 project authors. All rights reserved.
// AUTO-GENERATED BY tools/generate-runtime-tests.py, DO NOT MODIFY
// Flags: --allow-natives-syntax --harmony --harmony-proxies
var arg0 = %GetImplFromInitializedIntlObject(new Intl.Collator('en-US'));
var _string1 = "foo";
var _string2 = "foo";
%InternalCompare(arg0, _string1, _string2);