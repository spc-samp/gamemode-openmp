CREATE TABLE `jogadores` (
  `ID` INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `Nome` varchar(24),
  `Hash` varchar(60),
  `X_pos` FLOAT,
  `Y_pos` FLOAT,
  `Z_pos` FLOAT,
  `Angle` FLOAT,
  `Skin` INT,
  `Genero` INT
)