/*
 
 Copyright (c) 2012, SMB Phone Inc.
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies,
 either expressed or implied, of the FreeBSD Project.
 
 */

#pragma once

#include <hookflash/stack/hookflashTypes.h>

#include <list>
#include <boost/shared_array.hpp>

namespace hookflash
{
  namespace stack
  {
    interaction IPeerContactProfile
    {
      typedef zsLib::UINT UINT;
      typedef zsLib::String String;
      typedef zsLib::XML::ElementPtr ElementPtr;

      static IPeerContactProfilePtr createFromXML(
                                                  ElementPtr contactProfileBundleOrContactProfileElement,
                                                  const char *contactProfileSecret = NULL        // can be set later
                                                  );

      static IPeerContactProfilePtr createExternalFromPrivateProfile(ElementPtr privateProfileElement);

      virtual bool isReadOnly() const = 0;
      virtual bool isExternal() const = 0;

      virtual UINT getVersionNumber() const = 0;
      virtual bool setVersionNumber(UINT versionNumber) = 0;

      virtual String getContactID() const = 0;
      virtual String getContactProfileSecret() const = 0;

      virtual bool hasContactProfileSecret() const = 0;
      virtual bool usesContactProfileSecret(const char *contactProfileSecret) = 0;

      virtual void updateFrom(IPeerContactProfilePtr anotherVersion) = 0;

      virtual IPeerFilePublicPtr getPeerFilePublic() const = 0;

      virtual ElementPtr getPublicProfile() const = 0;
      virtual ElementPtr getPrivateProfile() const = 0;

      virtual bool setPublicProfile(ElementPtr profileElement) = 0;

      virtual bool setPrivateProfile(ElementPtr profileElement) = 0;

      virtual ElementPtr saveToXML() const = 0;
    };
  }
}
