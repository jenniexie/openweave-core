/*
 *
 *    Copyright (c) 2013-2017 Nest Labs, Inc.
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

import com.nestlabs.weave.security.WeaveCertificateSupport;

public class WeaveSecuritySupportTest extends SimpleTest
{
    public static void main(String[] args)
    {
        WeaveSecuritySupportTest testObj = new WeaveSecuritySupportTest();
        
        int res = testObj.runTests(new String[] {
            "testWeaveCertificateToX509",
            "testX509CertificateToWeave",
        });
        
        System.exit(res);
    }
    
    public void testWeaveCertificateToX509() throws Exception
    {
        byte[] convertedCert = WeaveCertificateSupport.weaveCertificateToX509(weaveCert);
        assertEqual(convertedCert, x509Cert, "X.509 converted cert");
    }

    public void testX509CertificateToWeave() throws Exception
    {
        byte[] convertedCert = WeaveCertificateSupport.x509CertificateToWeave(x509Cert);
        assertEqual(convertedCert, weaveCert, "Weave converted cert");
    }

    private static final byte[] weaveCert = toByteArray(new int[] {
        0xd5, 0x00, 0x00, 0x04, 0x00, 0x01, 0x00, 0x30, 0x01, 0x09, 0x00, 0xa8, 0x34, 0x22, 0xe9, 0xd9,
        0x75, 0xe4, 0x55, 0x24, 0x02, 0x04, 0x37, 0x03, 0x27, 0x13, 0x01, 0x00, 0x00, 0xee, 0xee, 0x30,
        0xb4, 0x18, 0x18, 0x26, 0x04, 0x95, 0x23, 0xa9, 0x19, 0x26, 0x05, 0x15, 0xc1, 0xd2, 0x2c, 0x37,
        0x06, 0x27, 0x13, 0x01, 0x00, 0x00, 0xee, 0xee, 0x30, 0xb4, 0x18, 0x18, 0x24, 0x07, 0x02, 0x26,
        0x08, 0x15, 0x00, 0x5a, 0x23, 0x30, 0x0a, 0x31, 0x04, 0x78, 0x52, 0xe2, 0x9c, 0x92, 0xba, 0x70,
        0x19, 0x58, 0x46, 0x6d, 0xae, 0x18, 0x72, 0x4a, 0xfb, 0x43, 0x0d, 0xf6, 0x07, 0x29, 0x33, 0x0d,
        0x61, 0x55, 0xe5, 0x65, 0x46, 0x8e, 0xba, 0x0d, 0xa5, 0x3f, 0xb5, 0x17, 0xc0, 0x47, 0x64, 0x44,
        0x02, 0x18, 0x4f, 0xa8, 0x11, 0x24, 0x50, 0xd4, 0x7b, 0x35, 0x83, 0x29, 0x01, 0x29, 0x02, 0x18,
        0x35, 0x82, 0x29, 0x01, 0x24, 0x02, 0x60, 0x18, 0x35, 0x81, 0x30, 0x02, 0x08, 0x42, 0x0c, 0xac,
        0xf6, 0xb4, 0x64, 0x71, 0xe6, 0x18, 0x35, 0x80, 0x30, 0x02, 0x08, 0x42, 0x0c, 0xac, 0xf6, 0xb4,
        0x64, 0x71, 0xe6, 0x18, 0x35, 0x0c, 0x30, 0x01, 0x19, 0x00, 0xbe, 0x0e, 0xda, 0xa1, 0x63, 0x5a,
        0x8e, 0xf1, 0x52, 0x17, 0x45, 0x80, 0xbd, 0xdc, 0x94, 0x12, 0xd4, 0xcc, 0x1c, 0x2c, 0x33, 0x4e,
        0x29, 0xdc, 0x30, 0x02, 0x19, 0x00, 0x8b, 0xe7, 0xee, 0x2e, 0x11, 0x17, 0x14, 0xae, 0x92, 0xda,
        0x2b, 0x3b, 0x6d, 0x2f, 0xd7, 0x5d, 0x9e, 0x5f, 0xcd, 0xb8, 0xba, 0x2f, 0x65, 0x76, 0x18, 0x18
    });
    
    private static final byte[] x509Cert = toByteArray(new int[] {
        0x30, 0x82, 0x01, 0x65, 0x30, 0x82, 0x01, 0x1b, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x09, 0x00,
        0xa8, 0x34, 0x22, 0xe9, 0xd9, 0x75, 0xe4, 0x55, 0x30, 0x09, 0x06, 0x07, 0x2a, 0x86, 0x48, 0xce,
        0x3d, 0x04, 0x01, 0x30, 0x22, 0x31, 0x20, 0x30, 0x1e, 0x06, 0x0a, 0x2b, 0x06, 0x01, 0x04, 0x01,
        0x82, 0xc3, 0x2b, 0x01, 0x03, 0x0c, 0x10, 0x31, 0x38, 0x42, 0x34, 0x33, 0x30, 0x45, 0x45, 0x45,
        0x45, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31, 0x30, 0x1e, 0x17, 0x0d, 0x31, 0x33, 0x30, 0x35, 0x32,
        0x33, 0x31, 0x39, 0x33, 0x31, 0x33, 0x33, 0x5a, 0x17, 0x0d, 0x32, 0x33, 0x30, 0x35, 0x32, 0x34,
        0x31, 0x39, 0x33, 0x31, 0x33, 0x33, 0x5a, 0x30, 0x22, 0x31, 0x20, 0x30, 0x1e, 0x06, 0x0a, 0x2b,
        0x06, 0x01, 0x04, 0x01, 0x82, 0xc3, 0x2b, 0x01, 0x03, 0x0c, 0x10, 0x31, 0x38, 0x42, 0x34, 0x33,
        0x30, 0x45, 0x45, 0x45, 0x45, 0x30, 0x30, 0x30, 0x30, 0x30, 0x31, 0x30, 0x49, 0x30, 0x13, 0x06,
        0x07, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x02, 0x01, 0x06, 0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x03,
        0x01, 0x01, 0x03, 0x32, 0x00, 0x04, 0x78, 0x52, 0xe2, 0x9c, 0x92, 0xba, 0x70, 0x19, 0x58, 0x46,
        0x6d, 0xae, 0x18, 0x72, 0x4a, 0xfb, 0x43, 0x0d, 0xf6, 0x07, 0x29, 0x33, 0x0d, 0x61, 0x55, 0xe5,
        0x65, 0x46, 0x8e, 0xba, 0x0d, 0xa5, 0x3f, 0xb5, 0x17, 0xc0, 0x47, 0x64, 0x44, 0x02, 0x18, 0x4f,
        0xa8, 0x11, 0x24, 0x50, 0xd4, 0x7b, 0xa3, 0x4b, 0x30, 0x49, 0x30, 0x0f, 0x06, 0x03, 0x55, 0x1d,
        0x13, 0x01, 0x01, 0xff, 0x04, 0x05, 0x30, 0x03, 0x01, 0x01, 0xff, 0x30, 0x0e, 0x06, 0x03, 0x55,
        0x1d, 0x0f, 0x01, 0x01, 0xff, 0x04, 0x04, 0x03, 0x02, 0x01, 0x06, 0x30, 0x11, 0x06, 0x03, 0x55,
        0x1d, 0x0e, 0x04, 0x0a, 0x04, 0x08, 0x42, 0x0c, 0xac, 0xf6, 0xb4, 0x64, 0x71, 0xe6, 0x30, 0x13,
        0x06, 0x03, 0x55, 0x1d, 0x23, 0x04, 0x0c, 0x30, 0x0a, 0x80, 0x08, 0x42, 0x0c, 0xac, 0xf6, 0xb4,
        0x64, 0x71, 0xe6, 0x30, 0x09, 0x06, 0x07, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x04, 0x01, 0x03, 0x39,
        0x00, 0x30, 0x36, 0x02, 0x19, 0x00, 0xbe, 0x0e, 0xda, 0xa1, 0x63, 0x5a, 0x8e, 0xf1, 0x52, 0x17,
        0x45, 0x80, 0xbd, 0xdc, 0x94, 0x12, 0xd4, 0xcc, 0x1c, 0x2c, 0x33, 0x4e, 0x29, 0xdc, 0x02, 0x19,
        0x00, 0x8b, 0xe7, 0xee, 0x2e, 0x11, 0x17, 0x14, 0xae, 0x92, 0xda, 0x2b, 0x3b, 0x6d, 0x2f, 0xd7,
        0x5d, 0x9e, 0x5f, 0xcd, 0xb8, 0xba, 0x2f, 0x65, 0x76
    });
}
