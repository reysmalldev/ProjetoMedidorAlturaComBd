
#include <ESP8266WiFi.h>           // Use this for WiFi instead of Ethernet.h
//#include <MySQL_Generic.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>


IPAddress server_addr(85, 10, 205, 173);  // IP of the MySQL *server* here localhost: 192.168.10.6 db4free: 85.10.205.173
char user[] = "usercaue_14";              // MySQL user login username
char password[] = "mlkzicka";        // MySQL user login password  

// Sample query UPDATE pessoa SET altura = 1.65 WHERE altura = 0"
char INSERT_SQL[] = "UPDATE db_caue14.pessoa SET altura = 1.65 WHERE altura = 0";

// WiFi card example
char ssid[] = "ANDRADE";         // your SSID
char pass[] = "192530Pecf";     // your SSID Password

WiFiClient client;                 // Use this for WiFi instead of EthernetClient
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

void setup()
{
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  // Begin WiFi section
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // print out info about the connection:
  Serial.println("\nConnected to network");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());

  Serial.print("Connecting to SQL...  ");
  if (conn.connect(server_addr, 3306, user, password))
    Serial.println("OK.");
  else
    Serial.println("FAILED.");
  
  // create MySQL cursor object
  cursor = new MySQL_Cursor(&conn);
}

void loop()
{
  if (conn.connected())
    cursor->execute(INSERT_SQL);

  delay(5000);
}
