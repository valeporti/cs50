-- MySQL dump 10.13  Distrib 5.5.46, for debian-linux-gnu (x86_64)
--
-- Host: 0.0.0.0    Database: cafeteria
-- ------------------------------------------------------
-- Server version	5.5.46-0ubuntu0.14.04.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `almacen`
--

DROP TABLE IF EXISTS `almacen`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `almacen` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `ingredientes` varchar(100) NOT NULL,
  `unidad` varchar(100) NOT NULL,
  `cantidad` decimal(10,4) NOT NULL,
  `consumoD` decimal(10,4) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `ingYuni` (`ingredientes`,`unidad`) COMMENT 'ingrediente más unidad'
) ENGINE=InnoDB AUTO_INCREMENT=57 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `almacen`
--

LOCK TABLES `almacen` WRITE;
/*!40000 ALTER TABLE `almacen` DISABLE KEYS */;
INSERT INTO `almacen` VALUES (1,3,'Eggs','piece',9.0000,0.6042),(2,3,'Milk','lt',4.0000,0.6042),(3,3,'Avocado','pieces',10.0000,2.7498),(10,3,'Tomato','pieces',0.0000,1.3749),(17,3,'Lemon','pieces',2.0000,3.4648),(18,3,'Chili','pieces',4.0000,0.6875),(24,3,'Olives','pieces',2.0000,1.4300),(26,3,'Salt','spoon',1.0000,1.7324),(27,3,'Flour','gr',300.0000,60.4200),(30,3,'Salmon','gr',100.0000,35.7500),(55,3,'Sausage','pieces',0.0000,0.0000),(56,3,'Bread','pieces',6.0000,0.0000);
/*!40000 ALTER TABLE `almacen` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `menu`
--

DROP TABLE IF EXISTS `menu`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `menu` (
  `id` int(100) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `secc` varchar(25) CHARACTER SET utf8 NOT NULL,
  `platillo` varchar(25) NOT NULL,
  `precio` decimal(10,4) NOT NULL,
  `tipo` varchar(25) NOT NULL,
  KEY `id` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=93 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `menu`
--

LOCK TABLES `menu` WRITE;
/*!40000 ALTER TABLE `menu` DISABLE KEYS */;
INSERT INTO `menu` VALUES (53,3,'Dessert','Fondant',3.0000,'French'),(55,3,'Dessert','Flan',2.0000,'Mexican'),(56,3,'Dessert','IceCream',2.0000,'Regional'),(58,3,'Coffee','Capuccino',2.0000,'Italian'),(60,3,'ToDrink','Coke',2.0000,'International'),(61,3,'ToDrink','Water',1.0000,'International'),(62,3,'Coffee','Express',2.0000,'Italian'),(72,3,'Entries','Guacamole',3.0000,'Mexican'),(73,3,'Entries','Carpaccio',5.0000,'Gourmet'),(75,3,'ToDrink','Beer',2.0000,'International'),(76,6,'Bebidas','Rompope',70.0000,'Michoacana'),(77,6,'Bebidas','Mezcal',50.0000,'OaxaqueÃ±o'),(78,6,'Postres','Flan',25.0000,'Michoacana'),(79,6,'Salsas','Conserva de Jitomate',80.0000,'Italiana'),(92,3,'Entries','HotDogs',2.0000,'German');
/*!40000 ALTER TABLE `menu` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pedidos`
--

DROP TABLE IF EXISTS `pedidos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pedidos` (
  `id` int(100) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `platillo` varchar(25) NOT NULL,
  `datime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=281 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pedidos`
--

LOCK TABLES `pedidos` WRITE;
/*!40000 ALTER TABLE `pedidos` DISABLE KEYS */;
INSERT INTO `pedidos` VALUES (145,3,'Coke','2016-12-08 03:05:16'),(146,3,'Coke','2016-12-08 03:05:17'),(147,3,'Water','2016-12-08 03:05:19'),(148,3,'Water','2016-12-08 03:05:19'),(152,3,'Fondant','2016-12-08 03:05:27'),(153,3,'IceCream','2016-12-08 03:05:30'),(154,3,'Flan','2016-12-08 03:05:37'),(155,3,'Water','2016-12-08 03:08:01'),(156,3,'Coke','2016-12-08 03:08:02'),(157,3,'Coke','2016-12-08 03:08:03'),(158,3,'Water','2016-12-08 03:08:04'),(159,3,'Water','2016-12-08 03:08:05'),(170,3,'Fondant','2016-12-08 03:08:09'),(171,3,'Fondant','2016-12-08 03:08:10'),(172,3,'Fondant','2016-12-08 03:08:10'),(173,3,'Water','2016-12-08 03:08:25'),(174,3,'Water','2016-12-08 03:08:25'),(175,3,'Fondant','2016-12-08 03:08:54'),(176,3,'IceCream','2016-12-08 03:09:04'),(177,3,'IceCream','2016-12-08 03:09:05'),(178,3,'Guacamole','2016-12-08 03:39:31'),(179,3,'Guacamole','2016-12-08 03:39:31'),(180,3,'Carpaccio','2016-12-08 03:39:31'),(181,3,'Carpaccio','2016-12-08 03:39:32'),(182,3,'Carpaccio','2016-12-08 03:39:32'),(183,3,'Carpaccio','2016-12-08 03:39:32'),(184,3,'Carpaccio','2016-12-08 03:39:32'),(185,3,'Guacamole','2016-12-08 03:39:40'),(186,3,'Carpaccio','2016-12-08 03:39:41'),(187,3,'Carpaccio','2016-12-08 03:39:41'),(188,3,'Carpaccio','2016-12-08 03:39:42'),(189,3,'Express','2016-12-08 03:39:43'),(190,3,'Express','2016-12-08 03:39:44'),(191,3,'Capuccino','2016-12-08 03:39:44'),(192,3,'Flan','2016-12-08 03:39:45'),(193,3,'Flan','2016-12-08 03:39:45'),(194,3,'Coke','2016-12-19 00:43:39'),(195,3,'Water','2016-12-19 00:47:17'),(196,3,'Guacamole','2016-12-20 22:42:32'),(197,3,'Guacamole','2016-12-20 22:42:32'),(198,3,'Flan','2016-12-20 22:42:33'),(199,3,'IceCream','2016-12-20 22:42:34'),(200,3,'IceCream','2016-12-20 22:42:34'),(201,3,'Express','2016-12-20 22:42:37'),(202,3,'Express','2016-12-20 22:42:38'),(203,3,'Express','2016-12-20 22:42:59'),(204,3,'Capuccino','2016-12-20 22:43:08'),(205,3,'Capuccino','2016-12-20 22:44:07'),(206,3,'Capuccino','2016-12-22 03:18:27'),(207,3,'Capuccino','2016-12-22 03:18:48'),(208,3,'Guacamole','2016-12-22 04:22:42'),(209,3,'Guacamole','2016-12-22 04:24:04'),(210,3,'Guacamole','2016-12-22 04:25:09'),(211,3,'Flan','2016-12-22 04:27:16'),(212,3,'Flan','2016-12-22 04:28:17'),(213,3,'Guacamole','2016-12-22 04:28:34'),(214,3,'Capuccino','2016-12-22 04:29:28'),(215,3,'Capuccino','2016-12-22 04:29:30'),(216,3,'Express','2016-12-22 04:29:35'),(217,3,'Capuccino','2016-12-22 04:30:42'),(218,3,'Capuccino','2016-12-22 04:30:45'),(219,3,'Express','2016-12-22 04:30:48'),(220,3,'Fondant','2016-12-22 04:30:50'),(221,3,'Flan','2016-12-22 04:30:52'),(222,3,'Express','2016-12-22 04:32:30'),(223,3,'Guacamole','2016-12-22 04:46:36'),(224,3,'Carpaccio','2016-12-22 04:46:40'),(225,3,'Fondant','2016-12-24 05:11:18'),(226,3,'Fondant','2016-12-24 05:11:18'),(227,3,'Flan','2016-12-24 05:11:19'),(228,3,'Flan','2016-12-24 05:11:19'),(229,3,'Carpaccio','2016-12-24 05:11:21'),(230,3,'Carpaccio','2016-12-24 05:11:21'),(231,3,'Carpaccio','2016-12-24 05:23:04'),(232,3,'Guacamole','2016-12-24 05:23:06'),(233,3,'Guacamole','2016-12-24 05:23:06'),(234,6,'Rompope','2016-12-24 20:22:45'),(235,6,'Mezcal','2016-12-24 20:22:46'),(236,6,'Mezcal','2016-12-24 20:22:47'),(237,6,'Flan','2016-12-24 20:22:48'),(238,6,'Conserva de Jitomate','2016-12-24 20:22:49'),(239,6,'Conserva de Jitomate','2016-12-24 20:22:49'),(240,3,'IceCream','2016-12-24 20:24:03'),(241,3,'IceCream','2016-12-24 20:24:03'),(242,3,'Flan','2016-12-24 20:24:03'),(243,3,'Guacamole','2016-12-24 20:30:45'),(244,3,'Guacamole','2016-12-24 20:30:55'),(245,3,'Guacamole','2016-12-24 20:31:15'),(246,3,'Guacamole','2016-12-24 20:37:07'),(247,3,'Guacamole','2016-12-24 20:40:33'),(248,3,'Guacamole','2016-12-25 01:38:34'),(249,3,'Flan','2016-12-25 01:41:57'),(250,3,'Guacamole','2016-12-25 01:45:18'),(251,3,'Guacamole','2016-12-25 01:47:45'),(252,3,'Guacamole','2016-12-25 01:48:57'),(253,3,'Guacamole','2016-12-25 01:49:32'),(254,3,'Guacamole','2016-12-25 01:51:53'),(255,3,'Guacamole','2016-12-25 01:52:04'),(256,3,'Guacamole','2016-12-25 02:15:02'),(257,3,'Carpaccio','2016-12-25 02:15:24'),(258,3,'Express','2016-12-25 18:24:56'),(259,3,'Express','2016-12-25 18:24:57'),(260,3,'Express','2016-12-25 18:24:57'),(261,3,'Water','2016-12-25 18:35:44'),(262,3,'Express','2016-12-25 18:43:08'),(263,3,'Water','2016-12-25 18:43:11'),(264,3,'Water','2016-12-25 19:03:45'),(265,3,'Coke','2016-12-25 19:03:46'),(266,3,'Water','2016-12-25 19:16:32'),(267,3,'Coke','2016-12-26 03:26:11'),(280,3,'HotDogs','2016-12-26 07:24:05');
/*!40000 ALTER TABLE `pedidos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `recetas`
--

DROP TABLE IF EXISTS `recetas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `recetas` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `platillo` varchar(25) NOT NULL,
  `ingredientes` varchar(50) NOT NULL,
  `cantidad` decimal(10,4) unsigned NOT NULL,
  `unidad` varchar(25) NOT NULL,
  `numPersonas` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=94 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `recetas`
--

LOCK TABLES `recetas` WRITE;
/*!40000 ALTER TABLE `recetas` DISABLE KEYS */;
INSERT INTO `recetas` VALUES (63,3,'Carpaccio','Lemon',2.0000,'pieces',2),(64,3,'Carpaccio','Olives',4.0000,'pieces',2),(65,3,'Flan','Eggs',1.0000,'piece',1),(66,3,'Flan','Milk',1.0000,'lt',1),(67,3,'guacamole','Avocado',2.0000,'pieces',1),(68,3,'guacamole','Lemon',2.0000,'pieces',1),(69,3,'guacamole','Chili',0.5000,'pieces',1),(70,3,'guacamole','Tomato',1.0000,'pieces',1),(71,3,'Carpaccio','Salmon',100.0000,'gr',2),(73,3,'guacamole','Salt',1.0000,'spoon',1),(74,3,'Carpaccio','Salt',1.0000,'spoon',2),(75,3,'Flan','Flour',100.0000,'gr',1),(92,3,'Hot-Dogs','Sausage',2.0000,'pieces',1),(93,3,'Hot-Dogs','Bread',2.0000,'pieces',1);
/*!40000 ALTER TABLE `recetas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `test`
--

DROP TABLE IF EXISTS `test`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `test` (
  `text1` varchar(25) NOT NULL,
  `text2` varchar(25) NOT NULL,
  `num` int(5) unsigned NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `test`
--

LOCK TABLES `test` WRITE;
/*!40000 ALTER TABLE `test` DISABLE KEYS */;
INSERT INTO `test` VALUES ('','',4),('','',4),('pedidos','guacamole',4),('pedidos','fondant de chocolate',4);
/*!40000 ALTER TABLE `test` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `hash` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (3,'Vale','$2y$10$Qge1O6QDKDUx06CUe/4v4OlBIZaEI9mnQucZsb7aYGcBMroLYPwDq'),(4,'vas','$2y$10$pE6huBcQs4buB.5CmkDbleCbMaH528/AM8zWVX3Ivnjcg4PygYPQm'),(5,'Nico','$2y$10$AyiXjSQQr8En75tAk1YQpOlW60qtRd0A5BQjviIQgIarBRJXVNtkW'),(6,'Soco','$2y$10$Vmvh9PuWZ.iptcrK8TSSduSf8shZtvwI/ZYjuJZJKO6FN/Fr4IUnC');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-01-16  2:00:29
