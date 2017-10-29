--  motion status database
--  zxp, 2017-09-13
--
--  DISCRIPTION: 1st version for SQLite3
--  1. zxp 190913:update TABLE calibration, ADD min,max,create_date.
--

--DROP DATABASE IF EXISTS xray;
--CREATE DATABASE IF NOT EXISTS xray;
--USE xray;

SELECT 'CREATING DATABASE STRUCTURE' as 'INFO';
pragma foreign_keys=ON;
SELECT 'foreign_keys=on' as 'INFO';

--DROP TABLE IF EXISTS site,
--                     devices,
--                     devicestatus,
--                     motors,
--                     motorstatus;

--set storage_engine = InnoDB;

--select CONCAT('storage engine: ', @@storage_engine) as INFO;

CREATE TABLE site (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    serialno    VARCHAR(64),
    productno   VARCHAR(64),
    create_date DATETIME,
    
    update_date DATETIME,
    expire_date DATETIME,
    profile     VARCHAR(512)
);

CREATE TABLE deviceType (
    type        INTEGER PRIMARY KEY AUTOINCREMENT,
    name        VARCHAR(32)
);

CREATE TABLE device (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    siteid      INT NOT NULL,
    device_type INT NOT NULL,
    create_date DATETIME,
    update_date DATETIME,
    expire_date DATETIME,
    profile     VARCHAR(512),

    FOREIGN KEY (siteid) REFERENCES site (id)    ON UPDATE CASCADE,
    FOREIGN KEY (device_type) REFERENCES deviceType (type)    ON UPDATE CASCADE
);


CREATE TABLE axis (
    nodeid      INT NOT NULL,
    deviceid    INT NOT NULL,
    position    INT,
    velocity    float,
    torque      float,
    accelerate  float,
    current     float,
    voltage     float,
    create_date DATETIME,
    profile     VARCHAR(512),

    FOREIGN KEY (deviceid) REFERENCES device (id)    ON UPDATE CASCADE
);

CREATE TABLE calibration (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    deviceid    INT NOT NULL,
    nodeid      INT NOT NULL,
    gain        float,
    offset      float,
    max            INT,
    min            INT,
    create_date DATETIME,

    FOREIGN KEY (deviceid) REFERENCES device (id)    ON UPDATE CASCADE
);


INSERT INTO `site` (serialno,productno,create_date,update_date,expire_date, profile) VALUES ('2b004',   'Everest G3-646', NULL, NULL, NULL, NULL);
INSERT INTO `site` (serialno,productno,create_date,update_date,expire_date, profile) VALUES ('2b005',   'Everest G3-646', NULL, NULL, NULL, NULL);
INSERT INTO `site` (serialno,productno,create_date,update_date,expire_date, profile) VALUES ('2b006',   'Everest G3-656', NULL, NULL, NULL, NULL);
INSERT INTO `site` (serialno,productno,create_date,update_date,expire_date, profile) VALUES ('2b007',   'Everest G3-656', NULL, NULL, NULL, NULL);

INSERT INTO `deviceType` (name) VALUES ('OTS');
INSERT INTO `deviceType` (name) VALUES ('Table');
INSERT INTO `deviceType` (name) VALUES ('WS');
INSERT INTO `deviceType` (name) VALUES ('StandardTable');
INSERT INTO `deviceType` (name) VALUES ('ManualWS');

INSERT INTO `device` (siteid,device_type,create_date) VALUES (1, 1, NULL);
INSERT INTO `device` (siteid,device_type,create_date) VALUES (2, 2, NULL);
INSERT INTO `device` (siteid,device_type,create_date) VALUES (3, 3, NULL);
INSERT INTO `device` (siteid,device_type,create_date) VALUES (4, 4, NULL);
INSERT INTO `device` (siteid,device_type,create_date) VALUES (1, 5, NULL);

INSERT INTO `axis` (nodeid ,deviceid,position,velocity,torque,accelerate,current,voltage,create_date) VALUES (1, 1, 123456, 0, 10, 100, 1.6, 5.0, NULL);
INSERT INTO `axis` (nodeid ,deviceid,position,velocity,torque,accelerate,current,voltage,create_date) VALUES (1, 1, 23456, 2, 20, 50, 2.6, 5.1, NULL);
INSERT INTO `axis` (nodeid ,deviceid,position,velocity,torque,accelerate,current,voltage,create_date) VALUES (2, 1, 23456, 2, 20, 50, 2.6, 5.1, NULL);
INSERT INTO `axis` (nodeid ,deviceid,position,velocity,torque,accelerate,current,voltage,create_date) VALUES (1, 1, 3456, 5, 30, 0, 3.6, 5.2, NULL);

INSERT INTO `calibration` (deviceid,nodeid,gain,offset, max, min) VALUES (1, 1, 100, 20, 1000000, -100);
INSERT INTO `calibration` (deviceid,nodeid,gain,offset, max, min) VALUES (2, 1, 100, 20, 1000000, -100);
INSERT INTO `calibration` (deviceid,nodeid,gain,offset, max, min) VALUES (3, 1, 100, 20, 1000000, -100);
INSERT INTO `calibration` (deviceid,nodeid,gain,offset, max, min) VALUES (4, 2, 100, 20, 1000000, -100);
