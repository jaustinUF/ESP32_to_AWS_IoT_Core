#include <pgmspace.h>

#define THINGNAME "esp32_1" // thing name from AWS IoT Core

const char WIFI_SSID[] = "(--> yours!)"; // wifi network (ssid)              
const char WIFI_PASSWORD[] = "(--> yours!)"; // wifi newtork password
// enpoint AWS IoT > Connect one device > (section "Prepare your device" at bottom of page)
const char AWS_IOT_ENDPOINT[] = "(--> yours!)";

// Amazon Root CA 1 : 
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
(--> yours!)
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
(--> yours!)
-----END CERTIFICATE-----
)KEY";

// Device Private key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
(--> yours!)
-----END RSA PRIVATE KEY-----
)KEY";
