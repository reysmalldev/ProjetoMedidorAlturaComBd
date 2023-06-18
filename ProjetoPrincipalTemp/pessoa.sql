-- Comando para criar tabela pessoa caso precise
CREATE TABLE IF NOT EXISTS pessoa (
	cod_pessoa INT PRIMARY KEY AUTO_INCREMENT,
	nome VARCHAR(35) NOT NULL,
	curso VARCHAR(35) NOT NULL,
	modulo INT NOT NULL,
	idade INT NOT NULL,
	peso FLOAT NOT NULL,
	altura FLOAT DEFAULT 0);
