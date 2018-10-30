/*
 *
 *    Copyright (c) 2016-2017 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      This file implements a process to effect a functional test for
 *      the Weave profile status support string interfaces.
 *
 */

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif

#include <nlunit-test.h>
#include <inttypes.h>
#include <stdio.h>

#include <Weave/Core/WeaveCore.h>
#include <Weave/Profiles/WeaveProfiles.h>
#include <Weave/Profiles/common/CommonProfile.h>
#include <Weave/Profiles/bulk-data-transfer/BulkDataTransfer.h>
#include <Weave/Profiles/service-directory/ServiceDirectory.h>

#if WEAVE_CONFIG_LEGACY_WDM
// Specify Legacy to enable definition in legacy code
#include <Weave/Profiles/data-management/Legacy/DMConstants.h>
#endif // WEAVE_CONFIG_LEGACY_WDM

#include <Weave/Profiles/device-control/DeviceControl.h>
#include <Weave/Profiles/fabric-provisioning/FabricProvisioning.h>
#include <Weave/Profiles/network-provisioning/NetworkProvisioning.h>
#include <Weave/Profiles/security/WeaveSecurity.h>
#include <Weave/Profiles/software-update/SoftwareUpdateProfile.h>
#include <Weave/Profiles/service-provisioning/ServiceProvisioning.h>

#include "ToolCommon.h"

using namespace nl::Weave::Profiles;


// Test input data.


struct Profile_Status {
    WeaveProfileId id;
    const char *fmt;
    uint8_t statusCount;
    uint16_t statusCodes[20];
};

static struct Profile_Status sContext[] = {
    {
        kWeaveProfile_BDX,
        "[ BDX(%08" PRIX32 "):%" PRIu16 " ]",
        7,
        {
            BulkDataTransfer::kStatus_Overflow,
            BulkDataTransfer::kStatus_LengthTooShort,
            BulkDataTransfer::kStatus_XferFailedUnknownErr,
            BulkDataTransfer::kStatus_XferMethodNotSupported,
            BulkDataTransfer::kStatus_UnknownFile,
            BulkDataTransfer::kStatus_StartOffsetNotSupported,
            BulkDataTransfer::kStatus_Unknown,
        }
    },
    {
        kWeaveProfile_Common,
        "[ Common(%08" PRIX32 "):%" PRIu16 " ]",
        11,
        {
            Common::kStatus_Success,
            Common::kStatus_BadRequest,
            Common::kStatus_UnsupportedMessage,
            Common::kStatus_UnexpectedMessage,
            Common::kStatus_AuthenticationRequired,
            Common::kStatus_OutOfMemory,
            Common::kStatus_Relocated,
            Common::kStatus_Busy,
            Common::kStatus_Timeout,
            Common::kStatus_InternalError,
            Common::kStatus_Continue,
        }
    },
#if WEAVE_CONFIG_LEGACY_WDM
    {
        kWeaveProfile_WDM,
        "[ WDM(%08" PRIX32 "):%" PRIu16 " ]",
        6,
        {
            DataManagement_Legacy::kStatus_CancelSuccess,
            DataManagement_Legacy::kStatus_InvalidPath,
            DataManagement_Legacy::kStatus_UnknownTopic,
            DataManagement_Legacy::kStatus_IllegalReadRequest,
            DataManagement_Legacy::kStatus_IllegalWriteRequest,
            DataManagement_Legacy::kStatus_InvalidVersion,
        }
    },
#endif
    {
        kWeaveProfile_DeviceControl,
        "[ DeviceControl(%08" PRIX32 "):%" PRIu16 " ]",
        4,
        {
            DeviceControl::kStatusCode_FailSafeAlreadyActive,
            DeviceControl::kStatusCode_NoFailSafeActive,
            DeviceControl::kStatusCode_NoMatchingFailSafeActive,
            DeviceControl::kStatusCode_UnsupportedFailSafeMode,
        }
    },
    {
        kWeaveProfile_FabricProvisioning,
        "[ FabricProvisioning(%08" PRIX32 "):%" PRIu16 " ]",
        3,
        {
            FabricProvisioning::kStatusCode_AlreadyMemberOfFabric,
            FabricProvisioning::kStatusCode_NotMemberOfFabric,
            FabricProvisioning::kStatusCode_InvalidFabricConfig,
        }
    },
    {
        kWeaveProfile_NetworkProvisioning,
        "[ NetworkProvisioning(%08" PRIX32 "):%" PRIu16 " ]",
        9,
        {
            NetworkProvisioning::kStatusCode_UnknownNetwork,
            NetworkProvisioning::kStatusCode_TooManyNetworks,
            NetworkProvisioning::kStatusCode_InvalidNetworkConfiguration,
            NetworkProvisioning::kStatusCode_UnsupportedNetworkType,
            NetworkProvisioning::kStatusCode_UnsupportedWiFiMode,
            NetworkProvisioning::kStatusCode_UnsupportedWiFiRole,
            NetworkProvisioning::kStatusCode_UnsupportedWiFiSecurityType,
            NetworkProvisioning::kStatusCode_InvalidState,
            NetworkProvisioning::kStatusCode_TestNetworkFailed,
        }
    },
    {
        kWeaveProfile_Security,
        "[ Security(%08" PRIX32 "):%" PRIu16 " ]",
        11,
        {
            Security::kStatusCode_SessionAborted,
            Security::kStatusCode_PASESupportsOnlyConfig1,
            Security::kStatusCode_NoCommonPASEConfigurations,
            Security::kStatusCode_UnsupportedEncryptionType,
            Security::kStatusCode_InvalidKeyId,
            Security::kStatusCode_DuplicateKeyId,
            Security::kStatusCode_KeyConfirmationFailed,
            Security::kStatusCode_InternalError,
            Security::kStatusCode_AuthenticationFailed,
            Security::kStatusCode_UnsupportedCASEConfiguration,
            Security::kStatusCode_UnsupportedCertificate,
         }
    },
    {
        kWeaveProfile_ServiceDirectory,
        "[ ServiceDirectory(%08" PRIX32 "):%" PRIu16 " ]",
        1,
        {
            ServiceDirectory::kStatus_DirectoryUnavailable,
        }
    },
    {
        kWeaveProfile_ServiceProvisioning,
        "[ ServiceProvisioning(%08" PRIX32 "):%" PRIu16 " ]",
        9,
        {
            ServiceProvisioning::kStatusCode_TooManyServices,
            ServiceProvisioning::kStatusCode_ServiceAlreadyRegistered,
            ServiceProvisioning::kStatusCode_InvalidServiceConfig,
            ServiceProvisioning::kStatusCode_NoSuchService,
            ServiceProvisioning::kStatusCode_PairingServerError,
            ServiceProvisioning::kStatusCode_InvalidPairingToken,
            ServiceProvisioning::kStatusCode_PairingTokenOld,
            ServiceProvisioning::kStatusCode_ServiceCommuncationError,
            ServiceProvisioning::kStatusCode_ServiceConfigTooLarge,
        }
    },
    {
        kWeaveProfile_SWU,
        "[ SWU(%08" PRIX32 "):%" PRIu16 " ]",
        7,
        {
            SoftwareUpdate::kStatus_NoUpdateAvailable,
            SoftwareUpdate::kStatus_UpdateFailed,
            SoftwareUpdate::kStatus_InvalidInstructions,
            SoftwareUpdate::kStatus_DownloadFailed,
            SoftwareUpdate::kStatus_IntegrityCheckFailed,
            SoftwareUpdate::kStatus_Abort,
            SoftwareUpdate::kStatus_Retry,
        }
    },
};

static const size_t kTestElements = sizeof(sContext) / sizeof(sContext[0]);

static void CheckStatusReportStrStart(nlTestSuite *inSuite, void *inContext)
{
    char statusStr[1024];

    // init statusStr with default status sting, which is for the status that does not have a well defined description string
    // then compare the actural StatusReportStr(status) with statusStr to ensure that each status has its description sting
    for (size_t ith = 0; ith < kTestElements; ith++)
    {
        for (uint16_t jth = 0; jth < sContext[ith].statusCount; jth++)
        {
           snprintf(statusStr, sizeof(statusStr), sContext[ith].fmt, sContext[ith].id, sContext[ith].statusCodes[jth]);
           NL_TEST_ASSERT(inSuite, (strcmp(nl::StatusReportStr(sContext[ith].id, sContext[ith].statusCodes[jth]), statusStr) != 0));
        }
    }
}

/**
 *   Test Suite. It lists all the test functions.
 */
static const nlTest sTests[] = {
    NL_TEST_DEF("StatusReportStr", CheckStatusReportStrStart),

    NL_TEST_SENTINEL()
};

int main(void)
{
    nlTestSuite theSuite = {
        "status-report-strings",
        &sTests[0],
        NULL,
        NULL
    };

    // Generate machine-readable, comma-separated value (CSV) output.
    nl_test_set_output_style(OUTPUT_CSV);

    // Run test suit againt one context.
    nlTestRunner(&theSuite, &sContext);

    return nlTestRunnerStats(&theSuite);
}
