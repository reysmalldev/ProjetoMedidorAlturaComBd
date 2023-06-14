#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

// Configuração da rede WiFi
const char* ssid = "nome_da_rede";
const char* password = "senha_da_rede";

// Configurações do banco de dados MySQL
IPAddress server_addr(10, 112, 171, 164); // Endereço IP do servidor MySQL 10.112.171.164
int server_port = 3306; // Porta do servidor MySQL
const char* db_user = "r";
const char* db_password = "";
const char* database = "bdaltura";

// Objeto de conexão WiFi
WiFiClient client;

// Objeto de conexão MySQL
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // Conexão WiFi
  Serial.println();
  Serial.print("Conectando à rede WiFi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Conexão WiFi estabelecida!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  
  // Conexão MySQL
  Serial.print("Conectando ao servidor MySQL: ");
  
  if (conn.connect(server_addr, server_port, db_user, db_password)) {
    Serial.println("Conexão MySQL estabelecida!");
    
    // Executa uma consulta
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    char query[128];
    sprintf(query, "SELECT * FROM tabela");
    
    cur_mem->execute(query);
    
    // Recupera os resultados
    MySQL_Row row;
    do {
      row = cur_mem->get_next_row();
      
      if (row.lengths(0) > 0) {
        Serial.print("Valor: ");
        Serial.println(row.getString(0));
      }
    } while (row.lengths(0) > 0);
    
    delete cur_mem;
  } else {
    Serial.println("Falha na conexão MySQL!");
  }
}

void loop() {
  // Seu código aqui
}