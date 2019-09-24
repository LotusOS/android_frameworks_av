/*
 * Copyright (C) 2019 The Android Open Source Project
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

#pragma once

#include <media/AudioPort.h>
#include <utils/Errors.h>
#include <cutils/config_utils.h>
#include <system/audio.h>
#include <system/audio_policy.h>

namespace android {

class DeviceDescriptorBase : public AudioPort, public AudioPortConfig
{
public:
     // Note that empty name refers by convention to a generic device.
    explicit DeviceDescriptorBase(audio_devices_t type);

    virtual ~DeviceDescriptorBase() {}

    audio_devices_t type() const { return mDeviceType; }
    std::string address() const { return mAddress; }
    void setAddress(const std::string &address) { mAddress = address; }

    // AudioPortConfig
    virtual sp<AudioPort> getAudioPort() const {
        return static_cast<AudioPort*>(const_cast<DeviceDescriptorBase*>(this));
    }
    virtual void toAudioPortConfig(struct audio_port_config *dstConfig,
            const struct audio_port_config *srcConfig = NULL) const;

    // AudioPort
    virtual void toAudioPort(struct audio_port *port) const;

    void dump(std::string *dst, int spaces, int index,
              const char* extraInfo = nullptr, bool verbose = true) const;
    void log() const;
    std::string toString() const;

protected:
    std::string mAddress{""};
    audio_devices_t     mDeviceType;
};

} // namespace android