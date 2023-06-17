-- Comando para criar tablea pessoa caso precise
CREATE TABLE pessoa (
	cod_pessoa INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
	nome VARCHAR(35) NOT NULL,
	idade INT NOT NULL,
	peso FLOAT NOT NULL,
	altura FLOAT NULL);
