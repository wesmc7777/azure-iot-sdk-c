// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hsm_client_data.h"

// This sample is provided for sample only.  Please do not use this in production
// For more information please see the devdoc using_custom_hsm.md
static const char* const COMMON_NAME = "custom-hsm-device-03";
static const char* const CERTIFICATE = "-----BEGIN CERTIFICATE-----\n"
"MIIFlDCCA3ygAwIBAgIBBzANBgkqhkiG9w0BAQsFADA0MTIwMAYDVQQDDClBenVy"
"ZSBJb1QgSHViIEludGVybWVkaWF0ZSBDZXJ0IFRlc3QgT25seTAeFw0yMDEwMjcx"
"MDQ2MzRaFw0yMDExMjYxMDQ2MzRaMB8xHTAbBgNVBAMMFGN1c3RvbS1oc20tZGV2"
"aWNlLTAzMIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAzDmnQA4cOZNm"
"f92Bi/Yf8Dq03cleawkPI7eRee0wuKurzvFaBXUSe+DMgtWQl8foBo9jbAxonQmK"
"TSaqV3aky7xrjLoP0thfFTLtZsUjXH/WP2iWn9GtFILHpe2po+bIkxa1AG165l/y"
"zm6ogrw36AP0ZZ3eNEHXbgHIodzP9YxjGtUQAoiY4Y/Wk63+83bTyMHX1ZVeppbT"
"hJiRzkmhyKAwVOuoxmbt8VzQ/+7TWW+XfCDbHMVDybTwoSB+sDYo0XZT1Bmo2hqg"
"wlBoe8vQFkGMq9zvQtwL0Mux1pl7jnMC/iT2tY7Hc4b5QPoDBjHoJGD9BDVCM2Rc"
"N9ostTCxpnUo4Kj5a7NI39K6etcSvxGZvexAPnTLiuNlnnXw0zwTb5j6P+FawM3t"
"Sth5XtntDxBt28kJg0Nyf2fChTCyZQK7bo2xpHAiXF/C9/JThaQUoF+wx/sRjQvt"
"j9DYcZJw2VxIj7g8AFpiGz5BB7+tMjvOTXG79/ZLg5QKLvwyREwpikO9eEFM9oDi"
"uCiMVnxOGbFmzCo9rtO3NcXi6k9KqOnhu0ZUW97FLvMxe3Dx2i45RhEMd20mkMUW"
"nw+8dphcHi1dV/LWYiHcuXg0ms2XhTBu8oWvBRYXf/5xd7Cf4yU31FcReco2NAsI"
"mIOckYt9R0++MDqWtPi1M3BnLtGWwisCAwEAAaOBxTCBwjAJBgNVHRMEAjAAMBEG"
"CWCGSAGG+EIBAQQEAwIFoDAzBglghkgBhvhCAQ0EJhYkT3BlblNTTCBHZW5lcmF0"
"ZWQgQ2xpZW50IENlcnRpZmljYXRlMB0GA1UdDgQWBBT4em03In/jqB2xYoVTRIuM"
"w3Sa6DAfBgNVHSMEGDAWgBSN+nYLPU6C91B2p+ckodWt5VX1izAOBgNVHQ8BAf8E"
"BAMCBeAwHQYDVR0lBBYwFAYIKwYBBQUHAwIGCCsGAQUFBwMEMA0GCSqGSIb3DQEB"
"CwUAA4ICAQAjgtxWPCVzDPwSNAsXPW4r9xy5Vc8Ctu/qEJtKMyG3MqFloZE9yIda"
"PSdwNGF8AwBWtu6koH2MTidjABmufN6+9C+fvKjve7Pr6eZi1fn7lZGelaPNFuVd"
"4TK5j+aJbt1siQDXjz9vSSx+R6FDwuEXbZyywEdi0/eh25uh3oYxX3idIcMxD1aU"
"DtRS0FLRdNqdsvKCxR08vplhedyjTOQ6He5NIUIXbGtfbeDlF4XXaGYYwCM/I/se"
"RCEOXeVXQhMmrRWR77l+zXhvNisE221xeBJMck2Hr/AqpYanggINn6d1mT0/N9kj"
"SGBJuaSCvKPXan7Ndnfimz3kDOuByAxncZaGjJYaSkBKABfOnzorJMYHTUlOc5Si"
"ohJubX3CPF1n87RXbBg0qBMSJuqW5arP4x+6ML0NM3kP4l8nVVMRY9OVoBl21SQ0"
"mw0hSSXeCH6b1Z56i9yFi+H2tqSnxHmwfDpKCe8C5oMIT2DjT9DR1fmplvKsWJ0s"
"BHRcooz31coMvNNvqFIx5TB3gV8x0L0OZf/fG86mHysVe/1CnG1r5X2EvqHSzmmP"
"DP3VmEUyJ6EyKmYy+3GTuQjuaLasL1I3Uf770/HDrBKbMNjW8X8UQ+F9LbNgKkVb"
"traeMAG25vmtSD74YdjZ/IQ/DCm/7A/5A+QNr0Ij3wd3qhU0XUGNiw=="
"\n-----END CERTIFICATE-----\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFPDCCAySgAwIBAgIBATANBgkqhkiG9w0BAQsFADAqMSgwJgYDVQQDDB9BenVy"
"ZSBJb1QgSHViIENBIENlcnQgVGVzdCBPbmx5MB4XDTIwMTAyMzIxMzAzM1oXDTIw"
"MTEyMjIxMzAzM1owNDEyMDAGA1UEAwwpQXp1cmUgSW9UIEh1YiBJbnRlcm1lZGlh"
"dGUgQ2VydCBUZXN0IE9ubHkwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoIC"
"AQDMMMSUcecw/K9/a2miCK2oW9q3z193g/EhdSvHmD2u2XTdYjqk+x/e8ngdzUJY"
"PpEzcqY/iUtZy5PGAkJJbRT4RwiB2oRJkuE2mDPw76dd5QdECh0O5ArfC/1Rt+Dz"
"yHAk5s3S0WEWZKakfqjg4SiUv36JvNu2gAU12PHINGmAAS1tWsVLV0aFcv8hO7Mt"
"bg3okqG1yYx3yJcWvmrNjS9Ev+KIO7VsPIDM8HuBIysEpP8zc/+QXXZRp+rBD2eH"
"wzDYwJK+3g2QqVqhvQBtr01mqAYbQFEx3VWNhuP3/KFXPyfBwF2TQDygUWGFW+vs"
"DH+hcOaTlNvcE0Ysmg1/sSrFKwKQDHc35mgKfZ7i/U+eheScT7+KbEDQnYMqhgRO"
"dwUey3rZBhJBUtJQzlhvfNlA0tjInpGO4n/QbMXVbcd/ZOX5aBbJLvxICA6daBS5"
"Ccdod5YNzn3Ie38/fCcFlXXJIesjV46E1ML1wBpDHUtB4sWW08X5l3DQqiCjbOj0"
"NNSNQ6Kq5xSMziLyafg5SYgIrc2Dz1+gPhWnKXOEB2wqWnGchcoIfE3Eq0MvSa3F"
"HbPYr/s2rWJ6LeScnCWwBl1AMPFdcwY2uycJbiWVmkpSdvEn62Dnc8c3QDzvLVxY"
"MdsouvIhNR6HDWBhyoOYluw+3m4+KiabYHM9E9De3A+DqwIDAQABo2MwYTAdBgNV"
"HQ4EFgQUjfp2Cz1OgvdQdqfnJKHVreVV9YswHwYDVR0jBBgwFoAULfbUw+z0NWoo"
"74eBFwBi+oJ4ZX4wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAYYwDQYJ"
"KoZIhvcNAQELBQADggIBAFqnj65NF9HXejd0K5NyfRr+Y0qxQtuI06sgkR6S/c5K"
"ToSEISddY5BiK8S9p4anorb3jQs8ya1hy1iR2W0j9S3m+C46O1PAmqlNGRm0s7lg"
"ml/ZruHS0AOUrlr2FJKFJlTZO26s6L1w4WnrsiTBUqyeNsmUDi5MeedYcO1Ni+t5"
"EYAvKAO1bemua6GufZPGkm7xobnQcNlFABJ4OQ6UcMvNMRnD8/Y3I4JUsDIEVoRq"
"+rFYB6v3sHsWGGWZ9bL5qbxhNeTQdG8YnfNHdEo36hwMNCHC/uJ+X974Wszh8bkA"
"fqETS07shz1xtFf1RVyVEO1MAyH1lngPBofBqyS+oQcTMmoSBWfnmsuJxHSXGfRw"
"VtXbciqH+L7KcJcDxZS7GO4KnIpH6lH4P5b7/gaKp3Ja5OJmtGdUZoDvfk7FvYmo"
"nIeIMrTAHo3fpuE3sKcrJTq46rWsxMz1Dw93MkZYkLvVLMC4CkhZGfrX3xuhZ5jx"
"GOL8vvbkq93MUAvvqpevk0MzSkEhklK3/AqOmyNx79OkKqcwOaxYelvf/zj2TdzM"
"TZK8ivyoxRHKjVqmaUXFiLjYd06sD0iIjn5VN5EWrb4Sp+oSvkNP7LFlsf74UVPA"
"MpvqKAEAS8c2fYnc1BwPg3VeK8JaeSEiSMCeQ/k8mG3sDo/G0YwXJHkN2vP1CvW2"
"\n-----END CERTIFICATE-----\n"
"-----BEGIN CERTIFICATE-----\n"
"MIIFOjCCAyKgAwIBAgIJAPzMa6s7mj7+MA0GCSqGSIb3DQEBCwUAMCoxKDAmBgNV"
"BAMMH0F6dXJlIElvVCBIdWIgQ0EgQ2VydCBUZXN0IE9ubHkwHhcNMjAxMDIzMjEz"
"MDMwWhcNMjAxMTIyMjEzMDMwWjAqMSgwJgYDVQQDDB9BenVyZSBJb1QgSHViIENB"
"IENlcnQgVGVzdCBPbmx5MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEA"
"4lvUhxU/8dQfQt1rinG9WfcL5y2zLlxh3N16LJCn6Nb9GhDjpAXQrhFC2jK0YXhL"
"QRoSIBxMA8xXOz0yhOIs1Zlk3OxJrdkUbHkikyHBqRLTA5McVvvSCID5qb13JmJN"
"EiYzcBBbi8F6nRANtS5d1UbkjxV1mKlwt4cbYTD239gDKI5uL91RxML3nrVv/3nW"
"iRvqBs11H/T1nl48bAaU9BRea6yYiE4aqfFSVdmWGoYrEflvs0EQNJbNyUTqscvL"
"llzK7a1HmjjZb3fFm9ni/VEMckDrV4lyi7Nth+32FgWYeitKmFwBQ6xk9fwI00cO"
"A7RXI/3E/ckpBWLymxkKI1vbOF5zHP7f0YFH/hd5sjZWP6ihmAdg2HFf02kJEFUG"
"QS+WSYuzxYVdj0gviMe90a4gNcsRcxtEEXebI0r5kNT11n4kc9SOmY4S5PuocJtO"
"ewIC5dx36ZlmB9DqXSlcjZSSWJh72pE37fhd03QPHunw0LtDg7BclgrL/WvWSOfL"
"chOU2lKv8NbJxDnOZAClTw3g//LOGtawaZflRf6doe8MN8l3mGI2RoLzBJbcIsk9"
"/7O7ue38fbExajPMWmKkqZbQf+B1/DtQ6/5zLxOUp+AucNofdaUE1I+V/zvJ1MSu"
"YPqjvegh1A+qcM/E3JI0J+8PBW55RgeUkLDdRVFdyucCAwEAAaNjMGEwHQYDVR0O"
"BBYEFC321MPs9DVqKO+HgRcAYvqCeGV+MB8GA1UdIwQYMBaAFC321MPs9DVqKO+H"
"gRcAYvqCeGV+MA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgGGMA0GCSqG"
"SIb3DQEBCwUAA4ICAQCt7JY/73PX9fuoNqwLiLUQ8pWvqQmk61APWQz1GKXoIyh4"
"TEel6wZSVl4gwmN8o27esasCUdOSKqBtjj2t2CtxtMmGpqR644QUWDQRdD6C/qCh"
"kV4/E9vPOwii9L60NJ2YC8AYtP7FQUkoOfiGpMq/GEyPxGdAwmc9kT1EQ2v3YgOB"
"js1ACrzfqnDFtVsoIQ/Pr/3XeCg/NNTP3sTJ7KidwyVXkFfgyI2Mu2gcsgRSb2Ah"
"0jbhycGZ+3aEnANOVbBRTHM1Y1pE5Z+rbZYOl3BaoSpjJmFKtG7tIim5k9f5RY4e"
"kJbLiFWuUTduj8e4tDpoDiwHf1q8NTKVUpKpIc5R9tJMTHi+u0MPO+pEss1Bdlwt"
"EfNRXc6/pkg5qb+jRCidFvAI/rXMJ3K7eVf9rPQqCTqU+xUGllBzVfj8m5gRlLav"
"KjnjMe1oHXJIUotTQiWt720KAyqaSn8lhthOLTZdtq4H7gsoQaB12MiZgL/7FXTm"
"W0bX2brOeCYn4yWRmz6t0IMgjIkRSdak2rndCYlMj0+M0pV6+5T5zbZIyl+5BHBE"
"0ZE7C+CI32AHmLcSIWd+57qoA2QKmWbjnAUUc0mUnP/bavXkKIBbLK58JyodyZ/d"
"5qcegM8R8OHsWahHE+epdDDrDRbTB4Js3yXIRN9tFSVkfFNFUgu3BC2r+Lj8aA=="
"\n-----END CERTIFICATE-----";

#define USE_RSA_SYNTAX

#ifdef USE_RSA_SYNTAX
static const char* const PRIVATE_KEY = "-----BEGIN RSA PRIVATE KEY-----\n"
#else
static const char* const PRIVATE_KEY = "-----BEGIN PRIVATE KEY-----\n"
#endif
"MIIJJwIBAAKCAgEAzDmnQA4cOZNmf92Bi/Yf8Dq03cleawkPI7eRee0wuKurzvFa"
"BXUSe+DMgtWQl8foBo9jbAxonQmKTSaqV3aky7xrjLoP0thfFTLtZsUjXH/WP2iW"
"n9GtFILHpe2po+bIkxa1AG165l/yzm6ogrw36AP0ZZ3eNEHXbgHIodzP9YxjGtUQ"
"AoiY4Y/Wk63+83bTyMHX1ZVeppbThJiRzkmhyKAwVOuoxmbt8VzQ/+7TWW+XfCDb"
"HMVDybTwoSB+sDYo0XZT1Bmo2hqgwlBoe8vQFkGMq9zvQtwL0Mux1pl7jnMC/iT2"
"tY7Hc4b5QPoDBjHoJGD9BDVCM2RcN9ostTCxpnUo4Kj5a7NI39K6etcSvxGZvexA"
"PnTLiuNlnnXw0zwTb5j6P+FawM3tSth5XtntDxBt28kJg0Nyf2fChTCyZQK7bo2x"
"pHAiXF/C9/JThaQUoF+wx/sRjQvtj9DYcZJw2VxIj7g8AFpiGz5BB7+tMjvOTXG7"
"9/ZLg5QKLvwyREwpikO9eEFM9oDiuCiMVnxOGbFmzCo9rtO3NcXi6k9KqOnhu0ZU"
"W97FLvMxe3Dx2i45RhEMd20mkMUWnw+8dphcHi1dV/LWYiHcuXg0ms2XhTBu8oWv"
"BRYXf/5xd7Cf4yU31FcReco2NAsImIOckYt9R0++MDqWtPi1M3BnLtGWwisCAwEA"
"AQKCAgBIyBMu5NhyPHG/B/XvJ1vihUmH8QfRJX1bwUP7K+i9J5EnQyRN5ZccxtSb"
"m/jX3sp17AwGqbVuocPEEw+J9CJu6Ut676RMBAh+yZOJmKAtivGTz3Y+pr8EHEeC"
"ftyCKPE6WlFPQbUW/QLPRuiPDvztlts2i7hw7zYTYldaOBN08v8uxNfbz0qMuHJE"
"VzIRGjwHw+1jlMQSopXnH2h3GA6sLUqMOSAA9RW/etCRJU/1A6v89MihzDuIWw+W"
"nLoJmoOZgo4FfM+MSwkXtwhFdjFGfT3g0fAC5+DeHHnYfQJnld1vLUUvFx9FsMiL"
"u43wW0DcFiSVp1Vcc1vaG8rrF9t3UCnQTZemWT9HY9y5bvDT94/c364UO4aNnUu3"
"Qb6FxvXy9xwWVxm1n4lxqjpe4+s14MVIRK+DY9k7+FsTV+I1ro+uW4EPu0pt/F2S"
"yK+vSV9+A8G3yX3fRdGabMgDZR4rilWuadKc8pb/NomDe7tuZo1WCNQkPIGx/JGs"
"4LIZu7CsxMd/T1LMvjZ09KKlBAaq7zA3G80hMjekBsgVcjW7ZgawEft+SHAZx4+k"
"KK4bDTvmIPaD4ZS/KxW8qnVABukvjIIApVBAAqsZ0f234aXt7JmW3NID79DauLEo"
"GMwdKPS0EFvXhah80MV1TZgviXh1YOhaPAUYzKtlLZB1LaxOoQKCAQEA6qnqFPkI"
"zuYHa2YibszxZt1+dzeKPvJh31d4MCKk3Rf5ZJwRUYaDxGkwW+mcEvYhuv+C2cN5"
"1nIAqN9R7XRfhn+h8xFsUJN8q00p1Xv2psTgQAEvZ0roAv33IVJEWPTQNrvIxmZJ"
"/eB9CSvc0UBjawEuyWpfYKRSgGLXw/WeFpjyt1W0lDrk8nZ08nXGs/nSMxyfoEJP"
"tARBUTaIA8gaX0nRQ9CTPr3spoUom6sKnP6o12Wc7Lpyde7SqR0Zi0SMa9v62dn2"
"HK0V2tNLnllUgUNKLLRKhCDTz5oPXVV8cMJJFmifqy8m8t+ZBivPjc4+Ds/4FC5b"
"F7x7fjGLaa+xlQKCAQEA3ss+wBuzgoKrH4Nf87Z9/+ylWoU4KRpuHUAf5kBxCkfF"
"gVKt2Oo9X888xoZHSjU1XkCyAJgRBIRVVx8MpfXANGdTTIww+RWAiOKLnykbaE1Y"
"h9wwgJkrxKmewPJsY90Y4X3zMBSvPt51PbY5piO96g7KUs0AtHQhiA+Vc2+zKsv+"
"kFkp4yZeAfVTRI+M8oKAVmbdtXjAga3jawbUb/Pfp2AfZ0VkW0zQT6OO2c+8XwpD"
"Hj4lmpb9Hy5grRnr7yJIsdYZivfkP/1NRpNmx3JHzkK5mGkpTD6MKRltNuDC+6PU"
"xA72xzWsUZ0SZZLPvVJzu83I6ns9DfPU6nmnG/M0vwKCAQAURRsYNq7BGHOZnlfp"
"FEDh7s4GxEBn0Y4MucSC++sbwf9j5mtEjIcDR0bLGbHGnYYqXfnSj6UNlglijO/J"
"wBykRJAbq+ycRTEmpuKvMycKHsV0IeYTWRATehaHxVBsErGNmMjuAlXv3R1P1n8b"
"gCFWU+LTuSGF+ou51U/n+GZwc0O7/GY9y5yNKRhO/Udtsm2qxpUvRasW1KtDtZ8o"
"HHfStVCjN/gQGl2/wI7Sa4LeLs0s1fUpKa3LbBa8Tuwu8HvksTrI6J/uuDDEFy5X"
"/kVjaQmWNPie0ysYqqkbGdBG+TFRAzaPleIaZqAUPWKPUDpiEyrNq3do5HoSW3s8"
"ZNXFAoIBADwpQ/OaR1oJsO3ciu+DqviNzYTpDmZDBdMOOs7xPdUZ1mJ6kglOD26s"
"xmuRXPTT82pVK/vvFEFU/rp83ux9tP4xnJPCE4NfZAsSqcM71XPP1wUw10QSmHgN"
"mZnenJhG3u4dFas5Gq1uYthcOar8Yc8vWUEMrJEN/vP/yUqXshjvZvlRqnb1KFN9"
"DJQp81SVGtS6CEp1pf4el5eSC5GDmDRZR4GagmQJFQM8VlnIt8QuQDuNapgZB5cA"
"7ggwRL6ZUmn7N4CIOfFxlAlnykw3Nt6is/1NAGLfTPfYLt6vyNcswUqEA+19N9/9"
"+zbEcyZbencPNZ7j0nPPEQKUASUSAn8CggEAbdXBHHOkKVM2wmbuKm/iBg6jwuk5"
"a3v3f8rym21Y/8BOtUIHXh2R5hAIJ3OZj5Nw7/RcnVdjRuoM+Vybuuz+XOACUdoS"
"uluoD8uOteK9MrS8qSlZB+Grgukts0rgfQi+o7N2eoJFQy2LdKU4DE2wPscdByDN"
"Va7JiKhIZpzo+ucqocqXw3648R3QAzVyqs1S34wwCRMUgCziuZ89p1SwaSTZZ1OZ"
"5mtir2CvgSECjXkN5qC6xrwvwjQDPfJSM9YuJy231MTyqgSZp/y3Fb1cw2xU5p78"
"R+91ie3fq6U+xEyU0bdcAVw+0qb/GEuLE77vOUUGCLEqR6QFhX5fxFTK7Q=="
#ifdef USE_RSA_SYNTAX
"\n-----END RSA PRIVATE KEY-----";
#else
"\n-----END PRIVATE KEY-----";
#endif

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
