#include "web_server.h"
#include "nethercap_core.h"
#include "wifi_deauth.h"
#include "wifi_scanner.h"
#include "logger.h"
#include "buzzer.h"
#include "sd_card.h"
#include "ota_update.h"
#include "gpio_control.h"
#include "reserved_pins.h"
#include "ble_module.h"
#include "subghz.h"
#include "nfc_module.h"
#include "rfid_module.h"

WebServerModule webServer;

static const char DASHBOARD_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>MRJ V2 Dashboard</title>
<style>
*{margin:0;padding:0;box-sizing:border-box}
body{font-family:system-ui,Arial,sans-serif;background:#0f0f1a;color:#e0e0e0;padding:16px}
h1{color:#00d4ff;text-align:center;margin-bottom:16px;font-size:1.6rem}
.card{background:#1a1a2e;border-radius:12px;padding:14px;margin-bottom:12px;border:1px solid #2a2a4a}
.card h2{color:#e94560;font-size:15px;margin-bottom:10px}
.btn{background:#0f3460;color:#fff;border:none;padding:9px 14px;border-radius:6px;cursor:pointer;margin:4px 3px;font-size:13px}
.btn:hover{background:#e94560}
.btn:active{transform:scale(0.97)}
.btn.danger{background:#8b0000}
.btn.ok{background:#006400}
.status{color:#00ff88}
.grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(260px,1fr));gap:12px}
pre{background:#0a0a14;padding:10px;border-radius:8px;overflow:auto;font-size:11px;max-height:280px;white-space:pre-wrap}
input,select{background:#0a0a14;border:1px solid #333;color:#eee;padding:7px;border-radius:5px;margin:3px;width:90%}
.ota-box{margin-top:8px}
.progress{height:6px;background:#222;border-radius:3px;margin-top:8px;overflow:hidden}
.progress>div{height:100%;width:0;background:#00d4ff;transition:width .2s}
</style>
</head>
<body>
<h1>MRJ V2 Dashboard</h1>
<div class="grid">
  <div class="card">
    <h2>Status</h2>
    <p>Version: <span class="status" id="ver">-</span></p>
    <p>IP: <span class="status" id="ip">-</span></p>
    <p>Deauth: <span id="deauth">-</span> | Rogue: <span id="rogue">-</span></p>
    <p>Targets: <span id="targets">0</span> | Frames: <span id="frames">0</span></p>
    <button class="btn" onclick="fetchStatus()">Refresh</button>
  </div>

  <div class="card">
    <h2>WiFi Tools</h2>
    <button class="btn" onclick="api('GET','/api/wifi/scan')">Scan Networks</button>
    <button class="btn" onclick="api('POST','/api/deauth/start')">Start Deauth</button>
    <button class="btn danger" onclick="api('POST','/api/deauth/stop')">Stop Deauth</button>
    <button class="btn" onclick="api('POST','/api/nethercap/start')">Nethercap Portal</button>
    <button class="btn danger" onclick="api('POST','/api/nethercap/stop')">Stop Portal</button>
  </div>

  <div class="card">
    <h2>BLE Tools</h2>
    <button class="btn" onclick="api('POST','/api/ble/scan')">BLE Scan</button>
    <button class="btn" onclick="api('POST','/api/ble/spam/start')">BLE Spam</button>
    <button class="btn danger" onclick="api('POST','/api/ble/spam/stop')">Stop Spam</button>
  </div>

  <div class="card">
    <h2>Sub-GHz</h2>
    <button class="btn" onclick="api('POST','/api/subghz/scan')">Freq Scan</button>
    <button class="btn" onclick="api('POST','/api/subghz/rx/start')">RX Mode</button>
    <button class="btn danger" onclick="api('POST','/api/subghz/rx/stop')">Stop RX</button>
  </div>

  <div class="card">
    <h2>RFID / NFC</h2>
    <button class="btn" onclick="api('POST','/api/nfc/read')">Read NFC</button>
    <button class="btn" onclick="api('POST','/api/rfid/read')">Read RFID</button>
  </div>

  <div class="card">
    <h2>GPIO Control</h2>
    <input type="number" id="gpio-pin" placeholder="Pin number" min="0" max="39">
    <button class="btn" onclick="gpioToggle()">Toggle Pin</button>
    <button class="btn" onclick="gpioRead()">Read Pin</button>
    <button class="btn" onclick="api('GET','/available_pins')">List Safe Pins</button>
  </div>

  <div class="card">
    <h2>OTA Update</h2>
    <div class="ota-box">
      <input type="file" id="ota-file" accept=".bin">
      <button class="btn ok" onclick="doOTA()">Upload Firmware</button>
      <div class="progress"><div id="ota-bar"></div></div>
      <p id="ota-msg" style="font-size:12px;margin-top:6px"></p>
    </div>
  </div>
</div>


  <div class="card">
    <h2>Nethercap Portal Editor</h2>
    <p style="font-size:12px;color:#aaa;margin-bottom:8px">Edit HTML portal. Disimpan ke SD: /mrj_config/portal.html</p>
    <textarea id="portal-html" rows="12" style="width:100%;background:#0a0a14;color:#eee;border:1px solid #333;border-radius:8px;padding:10px;font-size:12px;font-family:monospace;" placeholder="Loading portal HTML..."></textarea>
    <div style="margin-top:8px">
      <button class="btn ok" onclick="savePortal()">Save to SD</button>
      <button class="btn" onclick="loadPortal()">Reload</button>
      <button class="btn danger" onclick="resetPortal()">Reset Default</button>
    </div>
    <p id="portal-msg" style="font-size:12px;margin-top:6px;color:#00ff88"></p>
  </div>

<div class="card" style="margin-top:8px">
  <h2>Logs / Response</h2>
  <pre id="logs">Ready.</pre>
</div>

<script>
const logEl = document.getElementById('logs');
function log(msg) {
  if (typeof msg === 'object') msg = JSON.stringify(msg, null, 2);
  logEl.textContent = new Date().toLocaleTimeString() + '  ' + msg + '\n' + logEl.textContent.slice(0, 4000);
}

async function api(method, url, body) {
  try {
    const opt = { method };
    if (body) { opt.headers = {'Content-Type':'application/json'}; opt.body = JSON.stringify(body); }
    const r = await fetch(url, opt);
    const t = await r.text();
    let data;
    try { data = JSON.parse(t); } catch(e) { data = t; }
    log(data);
    return data;
  } catch(e) {
    log('Error: ' + e.message);
  }
}

async function fetchStatus() {
  try {
    const r = await fetch('/status');
    const d = await r.json();
    document.getElementById('ver').textContent = d.version || '-';
    document.getElementById('ip').textContent = d.ip || '-';
    document.getElementById('deauth').textContent = d.deauth ? 'ON' : 'OFF';
    document.getElementById('rogue').textContent = d.rogue ? 'ON' : 'OFF';
    document.getElementById('targets').textContent = d.targets || 0;
    document.getElementById('frames').textContent = d.frames || 0;
    log(d);
  } catch(e) { log('Status error: ' + e.message); }
}

function gpioToggle() {
  const pin = document.getElementById('gpio-pin').value;
  if (!pin) { log('Enter pin number'); return; }
  api('POST', '/gpio/toggle?pin=' + pin);
}
function gpioRead() {
  const pin = document.getElementById('gpio-pin').value;
  if (!pin) { log('Enter pin number'); return; }
  api('GET', '/gpio/read?pin=' + pin);
}

async function doOTA() {
  const f = document.getElementById('ota-file').files[0];
  if (!f) { document.getElementById('ota-msg').textContent = 'Pilih file .bin dulu'; return; }
  document.getElementById('ota-msg').textContent = 'Uploading ' + f.name + ' ...';
  const bar = document.getElementById('ota-bar');
  bar.style.width = '0%';

  const xhr = new XMLHttpRequest();
  xhr.open('POST', '/ota');
  xhr.upload.onprogress = function(e) {
    if (e.lengthComputable) {
      const pct = Math.round(e.loaded / e.total * 100);
      bar.style.width = pct + '%';
      document.getElementById('ota-msg').textContent = 'Upload ' + pct + '%';
    }
  };
  xhr.onload = function() {
    document.getElementById('ota-msg').textContent = xhr.responseText;
    log(xhr.responseText);
    if (xhr.status === 200) {
      bar.style.width = '100%';
      setTimeout(() => location.reload(), 3000);
    }
  };
  xhr.onerror = function() {
    document.getElementById('ota-msg').textContent = 'Upload failed';
  };
  xhr.send(f);
}


async function loadPortal() {
  try {
    const r = await fetch('/api/portal/get');
    const t = await r.text();
    document.getElementById('portal-html').value = t;
    document.getElementById('portal-msg').textContent = 'Loaded (' + t.length + ' chars)';
  } catch(e) {
    document.getElementById('portal-msg').textContent = 'Load error: ' + e.message;
  }
}

async function savePortal() {
  const html = document.getElementById('portal-html').value;
  if (!html || html.length < 50) {
    document.getElementById('portal-msg').textContent = 'HTML terlalu pendek';
    return;
  }
  try {
    const r = await fetch('/api/portal/save', {
      method: 'POST',
      headers: {'Content-Type': 'text/html'},
      body: html
    });
    const t = await r.text();
    document.getElementById('portal-msg').textContent = t;
    log(t);
  } catch(e) {
    document.getElementById('portal-msg').textContent = 'Save error: ' + e.message;
  }
}

async function resetPortal() {
  if (!confirm('Reset portal ke default bawaan?')) return;
  try {
    const r = await fetch('/api/portal/reset', { method: 'POST' });
    const t = await r.text();
    document.getElementById('portal-msg').textContent = t;
    loadPortal();
  } catch(e) {
    document.getElementById('portal-msg').textContent = 'Reset error: ' + e.message;
  }
}

// Auto load portal when page opens
loadPortal();

fetchStatus();
setInterval(fetchStatus, 8000);
</script>
</body>
</html>
)rawliteral";

void WebServerModule::init() {
    server = new AsyncWebServer(DEFAULT_WEB_PORT);
    running = false;
    currentIP = "";
    logger.log(LOG_INFO, "WEB", "Web server initialized");
}

void WebServerModule::startAP() {
    WiFi.mode(WIFI_AP);
    String ssid = eeprom.getApSsid();
    String pass = eeprom.getApPass();
    if (!eeprom.isApPasswordSet() || pass.length() == 0) {
        WiFi.softAP(ssid.c_str(), NULL);
        logger.log(LOG_INFO, "WEB", ("AP Started (OPEN): " + ssid).c_str());
    } else {
        WiFi.softAP(ssid.c_str(), pass.c_str());
        logger.log(LOG_INFO, "WEB", ("AP Started: " + ssid).c_str());
    }
    currentIP = WiFi.softAPIP().toString();
    apMode = true;
}

void WebServerModule::startServer() {
    if (running) return;
    setupRoutes();
    server->begin();
    running = true;
    logger.log(LOG_INFO, "WEB", "Server started on port " + String(DEFAULT_WEB_PORT));
    buzzer.success();
}

void WebServerModule::stopServer() {
    if (!running) return;
    server->end();
    running = false;
    logger.log(LOG_INFO, "WEB", "Server stopped");
}

bool WebServerModule::isRunning() { return running; }
String WebServerModule::getIP() { return currentIP; }
void WebServerModule::setCallback(void (*cb)(String, String)) { actionCallback = cb; }

void WebServerModule::setupRoutes() {
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", DASHBOARD_HTML);
    });

    server->on("/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
        request->send(200, "application/json", getStatusJSON());
    });

    server->on("/api/wifi/scan", HTTP_GET, [](AsyncWebServerRequest *request) {
        int n = nethercap.scanNetworks();
        StaticJsonDocument<2048> doc;
        doc["count"] = n;
        JsonArray arr = doc.createNestedArray("networks");
        Target* t = nethercap.getTargets();
        for (int i = 0; i < n && i < 30; i++) {
            JsonObject o = arr.createNestedObject();
            o["ssid"] = t[i].ssid;
            o["rssi"] = t[i].rssi;
            o["ch"] = t[i].channel;
            o["selected"] = t[i].selected;
        }
        String out;
        serializeJson(doc, out);
        request->send(200, "application/json", out);
    });

    server->on("/api/deauth/start", HTTP_POST, [](AsyncWebServerRequest *request) {
        nethercap.startDeauthSelected();
        request->send(200, "application/json", "{\"ok\":true,\"msg\":\"Deauth started\"}");
    });

    server->on("/api/deauth/stop", HTTP_POST, [](AsyncWebServerRequest *request) {
        nethercap.stopDeauth();
        request->send(200, "application/json", "{\"ok\":true,\"msg\":\"Deauth stopped\"}");
    });

    server->on("/api/nethercap/start", HTTP_POST, [](AsyncWebServerRequest *request) {
        nethercap.startRogueAP();
        request->send(200, "application/json", "{\"ok\":true,\"msg\":\"Rogue AP / portal started\"}");
    });

    server->on("/api/nethercap/stop", HTTP_POST, [](AsyncWebServerRequest *request) {
        nethercap.stopRogueAP();
        request->send(200, "application/json", "{\"ok\":true,\"msg\":\"Rogue AP stopped\"}");
    });

    server->on("/api/ble/scan", HTTP_POST, [](AsyncWebServerRequest *request) {
        bleModule.startScan(5);
        request->send(200, "application/json", "{\"ok\":true,\"msg\":\"BLE scan started (5s)\"}");
    });

    server->on("/api/ble/spam/start", HTTP_POST, [](AsyncWebServerRequest *request) {
        bleModule.startSpam();
        request->send(200, "application/json", "{\"ok\":true,\"msg\":\"BLE spam started\"}");
    });

    server->on("/api/ble/spam/stop", HTTP_POST, [](AsyncWebServerRequest *request) {
        bleModule.stopSpam();
        request->send(200, "application/json", "{\"ok\":true,\"msg\":\"BLE spam stopped\"}");
    });

    server->on("/api/subghz/scan", HTTP_POST, [](AsyncWebServerRequest *request) {
        subGHz.freqScan();
        request->send(200, "application/json", "{\"ok\":true,\"msg\":\"Sub-GHz freq scan triggered\"}");
    });

    server->on("/api/subghz/rx/start", HTTP_POST, [](AsyncWebServerRequest *request) {
        subGHz.startReceive();
        request->send(200, "application/json", "{\"ok\":true,\"msg\":\"Sub-GHz RX started\"}");
    });

    server->on("/api/subghz/rx/stop", HTTP_POST, [](AsyncWebServerRequest *request) {
        subGHz.stopReceive();
        request->send(200, "application/json", "{\"ok\":true,\"msg\":\"Sub-GHz RX stopped\"}");
    });

    server->on("/api/nfc/read", HTTP_POST, [](AsyncWebServerRequest *request) {
        bool ok = nfcModule.readTag();
        StaticJsonDocument<256> doc;
        doc["ok"] = ok;
        if (ok) {
            NFCTag t = nfcModule.getLastTag();
            doc["uid"] = t.uidStr;
            doc["len"] = t.uidLen;
        } else {
            doc["msg"] = "No tag or module disabled";
        }
        String out;
        serializeJson(doc, out);
        request->send(200, "application/json", out);
    });

    server->on("/api/rfid/read", HTTP_POST, [](AsyncWebServerRequest *request) {
        bool ok = rfidModule.readCard();
        StaticJsonDocument<256> doc;
        doc["ok"] = ok;
        if (ok) {
            RFIDTag t = rfidModule.getLastCard();
            doc["uid"] = t.uidStr;
            doc["len"] = t.uidLen;
        } else {
            doc["msg"] = "No card or module disabled";
        }
        String out;
        serializeJson(doc, out);
        request->send(200, "application/json", out);
    });

    server->on("/gpio/toggle", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam("pin")) {
            int pin = request->getParam("pin")->value().toInt();
            if (ReservedPinManager::getInstance().isSafeForUser(pin)) {
                gpioControl.togglePin(pin);
                StaticJsonDocument<64> doc;
                doc["state"] = digitalRead(pin);
                String out;
                serializeJson(doc, out);
                request->send(200, "application/json", out);
            } else {
                request->send(403, "application/json", "{\"error\":\"pin reserved or invalid\"}");
            }
        } else {
            request->send(400, "application/json", "{\"error\":\"missing pin\"}");
        }
    });

    server->on("/gpio/read", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("pin")) {
            int pin = request->getParam("pin")->value().toInt();
            StaticJsonDocument<64> doc;
            doc["state"] = digitalRead(pin);
            String out;
            serializeJson(doc, out);
            request->send(200, "application/json", out);
        } else {
            request->send(400, "application/json", "{\"error\":\"missing pin\"}");
        }
    });

    server->on("/available_pins", HTTP_GET, [](AsyncWebServerRequest *request) {
        StaticJsonDocument<512> doc;
        JsonArray arr = doc.to<JsonArray>();
        for (int pin = 0; pin < 40; pin++) {
            if (ReservedPinManager::getInstance().isSafeForUser(pin)) {
                arr.add(pin);
            }
        }
        String output;
        serializeJson(doc, output);
        request->send(200, "application/json", output);
    });

    server->on("/ota", HTTP_POST,
        [](AsyncWebServerRequest *request) {
            // response sent from handleUpload
        },
        [](AsyncWebServerRequest *request, String filename, size_t index,
           uint8_t *data, size_t len, bool final) {
            ota.handleUpload(request, filename, index, data, len, final);
        }
    );


    // ===== Portal Editor APIs =====
    server->on("/api/portal/get", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (sdCard.isReady() && sdCard.exists("/mrj_config/portal.html")) {
            String html = sdCard.readFile("/mrj_config/portal.html", 16384);
            request->send(200, "text/html", html);
        } else {
            // Return built-in default
            request->send(200, "text/html", nethercap.getIndexHTML());
        }
    });

    server->on("/api/portal/save", HTTP_POST,
        [](AsyncWebServerRequest *request) {},
        NULL,
        [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
            static String body;
            if (index == 0) body = "";
            for (size_t i = 0; i < len; i++) body += (char)data[i];

            if (index + len == total) {
                if (!sdCard.isReady()) {
                    request->send(500, "text/plain", "SD Card not ready");
                    return;
                }
                // Ensure directory exists
                sdCard.createDir("/mrj_config");
                if (sdCard.writeFile("/mrj_config/portal.html", body.c_str())) {
                    request->send(200, "text/plain", "OK - Portal saved to SD (/mrj_config/portal.html)");
                    logger.log(LOG_INFO, "WEB", "Portal HTML saved to SD");
                } else {
                    request->send(500, "text/plain", "Failed to write portal.html");
                }
            }
        }
    );

    server->on("/api/portal/reset", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (sdCard.isReady() && sdCard.exists("/mrj_config/portal.html")) {
            sdCard.deleteFile("/mrj_config/portal.html");
            request->send(200, "text/plain", "OK - Custom portal deleted, using built-in default");
        } else {
            request->send(200, "text/plain", "Already using built-in default");
        }
    });

    server->onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    });
}


String WebServerModule::getStatusJSON() {
    StaticJsonDocument<512> doc;
    doc["running"] = running;
    doc["deauth"] = nethercap.isDeauthRunning();
    doc["rogue"] = nethercap.isRogueAPActive();
    doc["targets"] = nethercap.getTargetCount();
    doc["frames"] = nethercap.getTotalDeauthFrames();
    doc["creds"] = nethercap.getCredentialCount();
    doc["clients"] = nethercap.getConnectedClients();
    doc["ip"] = currentIP;
    doc["version"] = FIRMWARE_VERSION;
    doc["ota"] = ota.isRunning();
    String output;
    serializeJson(doc, output);
    return output;
}
