/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _FSCRYPT_H_
#define _FSCRYPT_H_

#include <string>

// TODO: switch to <linux/fscrypt.h> once it's in Bionic
#define FSCRYPT_POLICY_FLAG_IV_INO_LBLK_64 0x08

bool fscrypt_is_native();

static const char* fscrypt_unencrypted_folder = "/unencrypted";
static const char* fscrypt_key_ref = "/unencrypted/ref";
static const char* fscrypt_key_per_boot_ref = "/unencrypted/per_boot_ref";
static const char* fscrypt_key_mode = "/unencrypted/mode";

namespace android {
namespace fscrypt {

struct EncryptionOptions {
    int version;
    int contents_mode;
    int filenames_mode;
    int flags;

    // Ensure that "version" is not valid on creation and so must be explicitly set
    EncryptionOptions() : version(0) {}
};

struct EncryptionPolicy {
    EncryptionOptions options;
    std::string key_raw_ref;
};

void BytesToHex(const std::string& bytes, std::string* hex);

bool OptionsToString(const EncryptionOptions& options, std::string* options_string);

bool ParseOptions(const std::string& options_string, EncryptionOptions* options);

bool EnsurePolicy(const EncryptionPolicy& policy, const std::string& directory);

}  // namespace fscrypt
}  // namespace android

#endif // _FSCRYPT_H_
