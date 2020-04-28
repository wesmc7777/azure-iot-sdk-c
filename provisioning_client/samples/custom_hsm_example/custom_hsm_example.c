// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hsm_client_data.h"

// This sample is provided for sample only.  Please do not use this in production
// For more information please see the devdoc using_custom_hsm.md
static const char* const COMMON_NAME = "custom-hsm-cert-device-02";
static const char* const CERTIFICATE = "-----BEGIN CERTIFICATE-----""\n"
"MIIFjzCCA3egAwIBAgIBBDANBgkqhkiG9w0BAQsFADAqMSgwJgYDVQQDDB9BenVy"
"ZSBJb1QgSHViIENBIENlcnQgVGVzdCBPbmx5MB4XDTIwMDQyOTAwMjE1NVoXDTIw"
"MDUyOTAwMjE1NVowJDEiMCAGA1UEAwwZY3VzdG9tLWhzbS1jZXJ0LWRldmljZS0w"
"MjCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAMePUFZwbfdRqLy8NLSg"
"I88Ok11KSKVV7hxu0G7iZHEQvc13Gcq+2++ZszQYCWdDUJ/juJVuVWBqNZhMSVpu"
"+MlH6HycbNyuxKdJlR5kW90wXcIDLVr3vygB2DIL3d3CWKYOYUBWVBIUIr0/c/N0"
"VbuYHGmxxZVvUL9SiBtTD8HvoXgW3ZQhRVi5LHjMGA77xBFkeoh2gsU1r5wxMeZK"
"jMnjEyfXAE3XnEJqjp3ROI2VZ9ADaveG2BsmeOe50SB4zmEkQlz9gbYdTGA2eqEU"
"pfhuWJx+GzBh0HhSv7/970EPVfmu3VhTSAi4d55aHWjl1njrjR5g+XopIwI2lP1f"
"VFUf3nYEbpxPLV28sS/VsOfY4RADjfXhvYBslS1z3qIut9hMCdY0hJ/aHkXR/T+R"
"Ij6ZSQsbFJuVmfmKx0a17NEq1TJK/G9QOVv3MqHHSbNWnFIERpRVTESmrN6xzv1r"
"zU90ETmqXABiAOvT/nzPooaucah4Mcw8XNbRMlx6dJv9R+Bk/9iQTX1J50dbzaQJ"
"AlKUBBlErh48bYz8t9zAMIhEw1l8y7bjX6mbPdCXMC/zhXLf60+MtNSB0/o7T+qO"
"KcyhUxniSdglEo+LvELSTUvrSZeJlnjg28PsxibEmUn1b/tOwOf1BqLO/80F99Bk"
"EV0g3VvkTlRefYtNijIwPfUzAgMBAAGjgcUwgcIwCQYDVR0TBAIwADARBglghkgB"
"hvhCAQEEBAMCBaAwMwYJYIZIAYb4QgENBCYWJE9wZW5TU0wgR2VuZXJhdGVkIENs"
"aWVudCBDZXJ0aWZpY2F0ZTAdBgNVHQ4EFgQUZyiac+J6N4TIVLG2I/p3zK2+ESow"
"HwYDVR0jBBgwFoAUrgIaujTcPBfDZfM2pSktH/keBn0wDgYDVR0PAQH/BAQDAgXg"
"MB0GA1UdJQQWMBQGCCsGAQUFBwMCBggrBgEFBQcDBDANBgkqhkiG9w0BAQsFAAOC"
"AgEAGQX2vPS2cRlGgu3zFt8IPUBrtItt03ADY+l7jJ2q5jmA4mZoD8Pp/Dkx0cW7"
"/r9WimZnuinr7b98JBjJBR1UUW8kEq/gI6ZPw+pnndsuVoU7gho8rmhGnE0wGbSR"
"r1gbT+aAe0tsjto9iV37GZ4OCSCVQMBzl1T8q9YgyNP+etKcXad9XVOEOnYkTVCy"
"wreSBomYZdU1D23AB3PY3C/HX1R3b97bggXQYHIhxx7OPgPXBBaD04WEs6jXVlCa"
"WXF219i/7Ye2Ggp9KQSMxJ5OyDqcspR3eEckKlqFMn+X36jvHBjvWcZmSk947UEa"
"idSxwuXR8gaxIpL125PWRx4BNqy3zNLvs/JCRsV/DxQzUaVugnSqGNrKYwlTNkFm"
"Rqp7kj+LSIxYLH/3hb0sb0Fbj3+dypVoAegJX1KJdtCsQ4FLIabTYbc2/KuG56iH"
"jGsLBS5e9pGDYW+KTrsH+esj2/aLX/aR6Ceot4LQiPZaPDlpYlmtcwXXZ4ws8z38"
"Rr73RNcPWmZApmjtvH4aZVC8/DAdz1tjFscyx5i81qFJ9uRyniLCF1E/rgMucMPT"
"KXGR81qgaYMyDFNeqYQfqQEGQ4zlYQhhF1efBDOJXsdjJw34UTJSMe0Y8937O9ka"
"ZkHKNxoLIgambA5rX58z1tgfJlmb4gh/II2Mg2L4T150Nn8=""\n"
"-----END CERTIFICATE-----";
static const char* const PRIVATE_KEY = "-----BEGIN PRIVATE KEY-----""\n"
"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""\n"
"-----END PRIVATE KEY-----";

// Provided for sample only
static const char* const SYMMETRIC_KEY = "Symmetric Key value";
static const char* const REGISTRATION_NAME = "Registration Name";

// Provided for sample only, canned values
static const unsigned char EK[] = { 0x45, 0x6e, 0x64, 0x6f, 0x72, 0x73, 0x65, 0x6d, 0x65, 0x6e, 0x74, 0x20, 0x6b, 0x65, 0x79, 0x0d, 0x0a };
static const size_t EK_LEN = sizeof(EK)/sizeof(EK[0]);
static const unsigned char SRK[] = { 0x53, 0x74, 0x6f, 0x72, 0x65, 0x20, 0x72, 0x6f, 0x6f, 0x74, 0x20, 0x6b, 0x65, 0x79, 0x0d, 0x0a };
static const size_t SRK_LEN = sizeof(SRK) / sizeof(SRK[0]);
static const unsigned char ENCRYPTED_DATA[] = { 0x45, 0x6e, 0x63, 0x72, 0x79, 0x70, 0x74, 0x65, 0x64, 0x20, 0x64, 0x61, 0x74, 0x61, 0x0d, 0x0a };

typedef struct CUSTOM_HSM_SAMPLE_INFO_TAG
{
    const char* certificate;
    const char* common_name;
    const char* key;
    const unsigned char* endorsment_key;
    size_t ek_length;
    const unsigned char* storage_root_key;
    size_t srk_len;
    const char* symm_key;
    const char* registration_name;
} CUSTOM_HSM_SAMPLE_INFO;

int hsm_client_x509_init()
{
    return 0;
}

void hsm_client_x509_deinit()
{
}

int hsm_client_tpm_init()
{
    return 0;
}

void hsm_client_tpm_deinit()
{
}

HSM_CLIENT_HANDLE custom_hsm_create()
{
    HSM_CLIENT_HANDLE result;
    CUSTOM_HSM_SAMPLE_INFO* hsm_info = malloc(sizeof(CUSTOM_HSM_SAMPLE_INFO));
    if (hsm_info == NULL)
    {
        (void)printf("Failued allocating hsm info\r\n");
        result = NULL;
    }
    else
    {
        // TODO: initialize any variables here
        hsm_info->certificate = CERTIFICATE;
        hsm_info->key = PRIVATE_KEY;
        hsm_info->common_name = COMMON_NAME;
        hsm_info->endorsment_key = EK;
        hsm_info->ek_length = EK_LEN;
        hsm_info->storage_root_key = SRK;
        hsm_info->srk_len = SRK_LEN;
        hsm_info->symm_key = SYMMETRIC_KEY;
        hsm_info->registration_name = REGISTRATION_NAME;
        result = hsm_info;
    }
    return result;
}

void custom_hsm_destroy(HSM_CLIENT_HANDLE handle)
{
    if (handle != NULL)
    {
        CUSTOM_HSM_SAMPLE_INFO* hsm_info = (CUSTOM_HSM_SAMPLE_INFO*)handle;
        // Free anything that has been allocated in this module
        free(hsm_info);
    }
}

char* custom_hsm_get_certificate(HSM_CLIENT_HANDLE handle)
{
    char* result;
    if (handle == NULL)
    {
        (void)printf("Invalid handle value specified\r\n");
        result = NULL;
    }
    else
    {
        // TODO: Malloc the certificate for the iothub sdk to free
        // this value will be sent unmodified to the tlsio
        // layer to be processed
        CUSTOM_HSM_SAMPLE_INFO* hsm_info = (CUSTOM_HSM_SAMPLE_INFO*)handle;
        size_t len = strlen(hsm_info->certificate);
        if ((result = (char*)malloc(len + 1)) == NULL)
        {
            (void)printf("Failure allocating certificate\r\n");
            result = NULL;
        }
        else
        {
            strcpy(result, hsm_info->certificate);
        }
    }
    return result;
}

char* custom_hsm_get_key(HSM_CLIENT_HANDLE handle)
{
    char* result;
    if (handle == NULL)
    {
        (void)printf("Invalid handle value specified\r\n");
        result = NULL;
    }
    else
    {
        // TODO: Malloc the private key for the iothub sdk to free
        // this value will be sent unmodified to the tlsio
        // layer to be processed
        CUSTOM_HSM_SAMPLE_INFO* hsm_info = (CUSTOM_HSM_SAMPLE_INFO*)handle;
        size_t len = strlen(hsm_info->key);
        if ((result = (char*)malloc(len + 1)) == NULL)
        {
            (void)printf("Failure allocating certificate\r\n");
            result = NULL;
        }
        else
        {
            strcpy(result, hsm_info->key);
        }
    }
    return result;
}

char* custom_hsm_get_common_name(HSM_CLIENT_HANDLE handle)
{
    char* result;
    if (handle == NULL)
    {
        (void)printf("Invalid handle value specified\r\n");
        result = NULL;
    }
    else
    {
        // TODO: Malloc the common name for the iothub sdk to free
        // this value will be sent to dps
        CUSTOM_HSM_SAMPLE_INFO* hsm_info = (CUSTOM_HSM_SAMPLE_INFO*)handle;
        size_t len = strlen(hsm_info->common_name);
        if ((result = (char*)malloc(len + 1)) == NULL)
        {
            (void)printf("Failure allocating certificate\r\n");
            result = NULL;
        }
        else
        {
            strcpy(result, hsm_info->common_name);
        }
    }
    return result;
}

int custom_hsm_get_endorsement_key(HSM_CLIENT_HANDLE handle, unsigned char** key, size_t* key_len)
{
    int result;
    if (handle == NULL || key == NULL || key_len == NULL)
    {
        (void)printf("Invalid parameter specified");
        result = __LINE__;
    }
    else
    {
        // TODO: Retrieve the endorsement key and malloc the value and return
        // it to the sdk
        CUSTOM_HSM_SAMPLE_INFO* hsm_info = (CUSTOM_HSM_SAMPLE_INFO*)handle;
        if ((*key = (unsigned char*)malloc(hsm_info->ek_length)) == NULL)
        {
            (void)printf("Failure allocating endorsement key\r\n");
            result = __LINE__;
        }
        else
        {
            memcpy(*key, hsm_info->endorsment_key, hsm_info->ek_length);
            *key_len = hsm_info->ek_length;
            result = 0;
        }
    }
    return result;
}

int custom_hsm_get_storage_root_key(HSM_CLIENT_HANDLE handle, unsigned char** key, size_t* key_len)
{
    int result;
    if (handle == NULL || key == NULL || key_len == NULL)
    {
        (void)printf("Invalid handle value specified");
        result = __LINE__;
    }
    else
    {
        // TODO: Retrieve the storage root key and malloc the value and return
        // it to the sdk
        CUSTOM_HSM_SAMPLE_INFO* hsm_info = (CUSTOM_HSM_SAMPLE_INFO*)handle;
        if ((*key = (unsigned char*)malloc(hsm_info->srk_len)) == NULL)
        {
            (void)printf("Failure allocating storage root key\r\n");
            result = __LINE__;
        }
        else
        {
            memcpy(*key, hsm_info->storage_root_key, hsm_info->srk_len);
            *key_len = hsm_info->srk_len;
            result = 0;
        }
    }
    return result;
}

int custom_hsm_sign_with_identity(HSM_CLIENT_HANDLE handle, const unsigned char* data, size_t data_len, unsigned char** key, size_t* key_len)
{
    int result;
    if (handle == NULL || data == NULL || key == NULL || key_len == NULL)
    {
        (void)printf("Invalid handle value specified");
        result = __LINE__;
    }
    else
    {
        (void)data;
        (void)data_len;

        // TODO: Need to implement signing the data variable and malloc the key and return it to the sdk

        size_t signed_data_len = 10;
        if ((*key = (unsigned char*)malloc(signed_data_len)) == NULL)
        {
            (void)printf("Failure allocating storage root key\r\n");
            result = __LINE__;
        }
        else
        {
            memcpy(*key, ENCRYPTED_DATA, signed_data_len);
            *key_len = signed_data_len;
            result = 0;
        }
    }
    return result;
}

int custom_hsm_activate_identity_key(HSM_CLIENT_HANDLE handle, const unsigned char* key, size_t key_len)
{
    int result;
    if (handle == NULL || key == NULL || key_len == 0)
    {
        (void)printf("Invalid handle value specified");
        result = __LINE__;
    }
    else
    {
        // Decrypt the key and store the value in the hsm
        result = 0;
    }
    return result;
}

char* custom_hsm_symm_key(HSM_CLIENT_HANDLE handle)
{
    char* result;
    if (handle == NULL)
    {
        (void)printf("Invalid handle value specified\r\n");
        result = NULL;
    }
    else
    {
        // TODO: Malloc the symmetric key for the iothub 
        // The SDK will call free() this value
        CUSTOM_HSM_SAMPLE_INFO* hsm_info = (CUSTOM_HSM_SAMPLE_INFO*)handle;
        size_t len = strlen(hsm_info->symm_key);
        if ((result = (char*)malloc(len + 1)) == NULL)
        {
            (void)printf("Failure allocating certificate\r\n");
            result = NULL;
        }
        else
        {
            strcpy(result, hsm_info->symm_key);
        }
    }
    return result;
}

char* custom_hsm_get_registration_name(HSM_CLIENT_HANDLE handle)
{
    char* result;
    if (handle == NULL)
    {
        (void)printf("Invalid handle value specified\r\n");
        result = NULL;
    }
    else
    {
        // TODO: Malloc the registration name for the iothub 
        // The SDK will call free() this value
        CUSTOM_HSM_SAMPLE_INFO* hsm_info = (CUSTOM_HSM_SAMPLE_INFO*)handle;
        size_t len = strlen(hsm_info->registration_name);
        if ((result = (char*)malloc(len + 1)) == NULL)
        {
            (void)printf("Failure allocating certificate\r\n");
            result = NULL;
        }
        else
        {
            strcpy(result, hsm_info->registration_name);
        }
    }
    return result;
}

// Defining the v-table for the x509 hsm calls
static const HSM_CLIENT_X509_INTERFACE x509_interface =
{
    custom_hsm_create,
    custom_hsm_destroy,
    custom_hsm_get_certificate,
    custom_hsm_get_key,
    custom_hsm_get_common_name
};

// Defining the v-table for the x509 hsm calls
static const HSM_CLIENT_TPM_INTERFACE tpm_interface =
{
    custom_hsm_create,
    custom_hsm_destroy,
    custom_hsm_activate_identity_key,
    custom_hsm_get_endorsement_key,
    custom_hsm_get_storage_root_key,
    custom_hsm_sign_with_identity
};

static const HSM_CLIENT_KEY_INTERFACE symm_key_interface =
{
    custom_hsm_create,
    custom_hsm_destroy,
    custom_hsm_symm_key,
    custom_hsm_get_registration_name
};

const HSM_CLIENT_TPM_INTERFACE* hsm_client_tpm_interface()
{
    // tpm interface pointer
    return &tpm_interface;
}

const HSM_CLIENT_X509_INTERFACE* hsm_client_x509_interface()
{
    // x509 interface pointer
    return &x509_interface;
}

const HSM_CLIENT_KEY_INTERFACE* hsm_client_key_interface()
{
    return &symm_key_interface;
}
