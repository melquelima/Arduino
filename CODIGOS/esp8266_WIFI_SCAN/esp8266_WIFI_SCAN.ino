#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "esp8266";
IPAddress    apIP(192, 168, 0, 1);

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
   String html;
   html += "<html><style>";
  html += "table{font-family:arial,sans-serif;border-collapse:collapse;width:100%;}";
  html += "td,th{border:1pxsolid#8aace2;text-align:center;padding:8px;}";
  html += "tr:nth-child(even){background-color:#8aace2;}";
  html += ".form-control{height:24px;padding:6px12px;font-size:14px;line-height:1.42857143;color:#555;background-color:#fff;background-image:none;border:1pxsolid#ccc;border-radius:4px;}";
  html += "hr{margin-top:20px;margin-bottom:20px;border:0;border-top:1pxsolid#eee}";
  html += ".form-inline.form-control{display:inline-block;width:auto;vertical-align:middle}";
  html += ".btn{padding:6px12px;font-size:16px;text-align:center;cursor:pointer;user-select:none;border:1pxsolidtransparent;border-radius:4px}";
  html += ".btn-default{color:#333;background-color:#fff;border-color:#ccc}";
  html += ".btn-block{display:block;width:100%}";
  html += "label{display:inline-block;max-width:100%;margin-bottom:5px;font-weight:700}";
  html += "</style><body><center>";
  html += "<form class=\"form-inline\"action=\" / connect.php\"><div style=\"width:30%; \">";
  html += "<table><tr><th></th><th>Id</th><th>Ssid</th></tr>";

  int n = WiFi.scanNetworks();

  for (int i = 0; i < n; ++i)
  {
    html += "<tr><th><input type=\"radio\" name=\"gender\" value=";
    html += WiFi.SSID(i);
    html += "\"></th><td>";
    html += i + 1;
    html += "</td><td>";
    html += WiFi.SSID(i);
    html += "</td></tr>";
    delay(10);
  }

  html += " </table><hr/><div class =\"form-group\"><label for=\"pwd\">Senha:</label>";
  html += "<input type=\"password\"class=\"form-control\"id =\"pwd\"placeholder =\"Insira a Senha\"name=\"pwd\"></div><br/>";
  html += "<button type = \"submit\"class = \"btn btn-default btn-block\">Enviar</button>";
  html += "</div></form></center></body></html>";
  Serial.println(html);
	server.send(200, "text/html", html);
}

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
	WiFi.softAP(ssid);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}
