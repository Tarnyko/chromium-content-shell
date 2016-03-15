// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_ANDROID_SHELL_MANAGER_H_
#define CONTENT_SHELL_ANDROID_SHELL_MANAGER_H_

#include <jni.h>

#include "base/android/jni_android.h"
#include "base/android/scoped_java_ref.h"

class Shell;

namespace blink {
class WebLayer;
}

namespace content {

// Creates an Android specific shell view, which is our version of a shell
// window.  This view holds the controls and content views necessary to
// render a shell window.  Returns the java object representing the shell view.
// object.
base::android::ScopedJavaLocalRef<jobject> CreateShellView(Shell* shell);

// Removes a previously created shell view.
void RemoveShellView(jobject shell_view);

// Registers the ShellManager native methods.
bool RegisterShellManager(JNIEnv* env);

void ShellAttachLayer(blink::WebLayer* layer);
void ShellRemoveLayer(blink::WebLayer* layer);
}  // namespace content

#endif  // CONTENT_SHELL_ANDROID_SHELL_MANAGER_H_
