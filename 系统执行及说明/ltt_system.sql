/*
 Navicat MySQL Data Transfer

 Source Server         : mysql
 Source Server Type    : MySQL
 Source Server Version : 80025
 Source Host           : localhost:3306
 Source Schema         : ltt_system

 Target Server Type    : MySQL
 Target Server Version : 80025
 File Encoding         : 65001

 Date: 08/07/2021 06:55:10
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for allowance
-- ----------------------------
DROP TABLE IF EXISTS `allowance`;
CREATE TABLE `allowance`  (
  `id` int NOT NULL,
  `person_id` int NULL DEFAULT NULL,
  `year` int NULL DEFAULT NULL,
  `month` int NULL DEFAULT NULL,
  `overtime` int NULL DEFAULT NULL,
  `overtime_type` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `fk_all_pid`(`person_id`) USING BTREE,
  CONSTRAINT `fk_all_pid` FOREIGN KEY (`person_id`) REFERENCES `person` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of allowance
-- ----------------------------
INSERT INTO `allowance` VALUES (1, 1, 2021, 1, 3, 2);
INSERT INTO `allowance` VALUES (2, 1, 2021, 3, 5, 2);
INSERT INTO `allowance` VALUES (3, 1, 2021, 5, 2, 3);
INSERT INTO `allowance` VALUES (4, 2, 2021, 2, 1, 1);
INSERT INTO `allowance` VALUES (5, 2, 2021, 4, 6, 2);
INSERT INTO `allowance` VALUES (6, 3, 2021, 1, 4, 2);
INSERT INTO `allowance` VALUES (7, 3, 2021, 2, 2, 2);
INSERT INTO `allowance` VALUES (8, 4, 2021, 3, 1, 1);
INSERT INTO `allowance` VALUES (9, 5, 2021, 3, 2, 2);
INSERT INTO `allowance` VALUES (10, 6, 2021, 3, 3, 1);
INSERT INTO `allowance` VALUES (11, 6, 2021, 4, 4, 2);
INSERT INTO `allowance` VALUES (12, 7, 2021, 1, 5, 3);
INSERT INTO `allowance` VALUES (13, 7, 2021, 3, 3, 2);
INSERT INTO `allowance` VALUES (14, 8, 2021, 3, 2, 2);
INSERT INTO `allowance` VALUES (15, 8, 2021, 4, 1, 2);
INSERT INTO `allowance` VALUES (16, 8, 2021, 5, 4, 1);
INSERT INTO `allowance` VALUES (17, 8, 2021, 6, 4, 2);

-- ----------------------------
-- Table structure for attendance
-- ----------------------------
DROP TABLE IF EXISTS `attendance`;
CREATE TABLE `attendance`  (
  `id` int NOT NULL,
  `person_id` int NULL DEFAULT NULL,
  `year` int NULL DEFAULT NULL,
  `month` int NULL DEFAULT NULL,
  `absence_time` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `fk_att_pid`(`person_id`) USING BTREE,
  CONSTRAINT `fk_att_pid` FOREIGN KEY (`person_id`) REFERENCES `person` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of attendance
-- ----------------------------
INSERT INTO `attendance` VALUES (1, 1, 2021, 1, 0);
INSERT INTO `attendance` VALUES (2, 1, 2021, 2, 2);
INSERT INTO `attendance` VALUES (3, 1, 2021, 3, 3);
INSERT INTO `attendance` VALUES (4, 1, 2021, 4, 0);
INSERT INTO `attendance` VALUES (5, 1, 2021, 5, 3);
INSERT INTO `attendance` VALUES (6, 2, 2021, 1, 0);
INSERT INTO `attendance` VALUES (7, 2, 2021, 2, 1);
INSERT INTO `attendance` VALUES (8, 2, 2021, 3, 2);
INSERT INTO `attendance` VALUES (9, 2, 2021, 4, 3);
INSERT INTO `attendance` VALUES (10, 2, 2021, 5, 3);
INSERT INTO `attendance` VALUES (11, 3, 2021, 1, 0);
INSERT INTO `attendance` VALUES (12, 3, 2021, 2, 0);
INSERT INTO `attendance` VALUES (13, 3, 2021, 3, 0);
INSERT INTO `attendance` VALUES (14, 3, 2021, 4, 0);
INSERT INTO `attendance` VALUES (15, 3, 2021, 5, 0);
INSERT INTO `attendance` VALUES (16, 4, 2021, 1, 2);
INSERT INTO `attendance` VALUES (17, 4, 2021, 2, 3);
INSERT INTO `attendance` VALUES (18, 4, 2021, 3, 1);
INSERT INTO `attendance` VALUES (19, 4, 2021, 4, 4);
INSERT INTO `attendance` VALUES (20, 4, 2021, 5, 5);
INSERT INTO `attendance` VALUES (21, 5, 2021, 1, 3);
INSERT INTO `attendance` VALUES (22, 5, 2021, 2, 3);
INSERT INTO `attendance` VALUES (23, 5, 2021, 3, 3);
INSERT INTO `attendance` VALUES (24, 5, 2021, 4, 2);
INSERT INTO `attendance` VALUES (25, 5, 2021, 5, 2);
INSERT INTO `attendance` VALUES (26, 6, 2021, 1, 1);
INSERT INTO `attendance` VALUES (27, 6, 2021, 2, 1);
INSERT INTO `attendance` VALUES (28, 6, 2021, 3, 0);
INSERT INTO `attendance` VALUES (29, 6, 2021, 4, 0);
INSERT INTO `attendance` VALUES (30, 6, 2021, 5, 2);
INSERT INTO `attendance` VALUES (31, 7, 2021, 1, 1);
INSERT INTO `attendance` VALUES (32, 7, 2021, 2, 0);
INSERT INTO `attendance` VALUES (33, 7, 2021, 3, 0);
INSERT INTO `attendance` VALUES (34, 7, 2021, 4, 0);
INSERT INTO `attendance` VALUES (35, 7, 2021, 5, 0);
INSERT INTO `attendance` VALUES (36, 8, 2021, 1, 1);
INSERT INTO `attendance` VALUES (37, 8, 2021, 2, 2);
INSERT INTO `attendance` VALUES (38, 8, 2021, 3, 3);
INSERT INTO `attendance` VALUES (39, 8, 2021, 4, 0);
INSERT INTO `attendance` VALUES (40, 8, 2021, 5, 0);
INSERT INTO `attendance` VALUES (41, 8, 2021, 6, 1);
INSERT INTO `attendance` VALUES (42, 7, 2021, 6, 2);

-- ----------------------------
-- Table structure for department
-- ----------------------------
DROP TABLE IF EXISTS `department`;
CREATE TABLE `department`  (
  `id` int NOT NULL,
  `name` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of department
-- ----------------------------
INSERT INTO `department` VALUES (1, '生产部');
INSERT INTO `department` VALUES (2, '项目部');
INSERT INTO `department` VALUES (3, '销售部');
INSERT INTO `department` VALUES (4, '财务部');

-- ----------------------------
-- Table structure for job
-- ----------------------------
DROP TABLE IF EXISTS `job`;
CREATE TABLE `job`  (
  `id` int NOT NULL,
  `name` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `level` int NOT NULL,
  `based_salary` int NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of job
-- ----------------------------
INSERT INTO `job` VALUES (0, '经理', 0, 300);
INSERT INTO `job` VALUES (1, '测绘人员', 1, 150);
INSERT INTO `job` VALUES (2, '测绘人员', 2, 100);
INSERT INTO `job` VALUES (3, '加工人员', 1, 200);
INSERT INTO `job` VALUES (4, '加工人员', 2, 150);
INSERT INTO `job` VALUES (5, '检测人员', 1, 150);
INSERT INTO `job` VALUES (6, '检测人员', 2, 100);
INSERT INTO `job` VALUES (7, '销售人员', 1, 150);

-- ----------------------------
-- Table structure for person
-- ----------------------------
DROP TABLE IF EXISTS `person`;
CREATE TABLE `person`  (
  `id` int NOT NULL,
  `name` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `gender` char(4) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `telephone` char(11) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `depart_id` int NULL DEFAULT NULL,
  `job_id` int NULL DEFAULT NULL,
  `status` int NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `fk_depart_id`(`depart_id`) USING BTREE,
  INDEX `fk_job_id`(`job_id`) USING BTREE,
  CONSTRAINT `fk_depart_id` FOREIGN KEY (`depart_id`) REFERENCES `department` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `fk_job_id` FOREIGN KEY (`job_id`) REFERENCES `job` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of person
-- ----------------------------
INSERT INTO `person` VALUES (1, '杨嘉佑', '男', '18110846585', 1, 0, 1);
INSERT INTO `person` VALUES (2, '韩白烨', '女', '15261855533', 2, 0, 1);
INSERT INTO `person` VALUES (3, '任听寒', '男', '14982563513', 3, 0, 1);
INSERT INTO `person` VALUES (4, '侯凝思', '女', '17061915416', 4, 0, 1);
INSERT INTO `person` VALUES (5, '曾刚豪', '男', '13306186777', 1, 1, 1);
INSERT INTO `person` VALUES (6, '彭博延', '男', '14747344393', 1, 3, 1);
INSERT INTO `person` VALUES (7, '贺贺', '男', '13376152760', 2, 5, 1);
INSERT INTO `person` VALUES (8, '苏雅', '女', '15623245732', 3, 7, 1);
INSERT INTO `person` VALUES (9, '玖流', '女', '15623283774', 2, 2, 0);

-- ----------------------------
-- Table structure for salary
-- ----------------------------
DROP TABLE IF EXISTS `salary`;
CREATE TABLE `salary`  (
  `id` int NOT NULL,
  `person_id` int NULL DEFAULT NULL,
  `year` int NULL DEFAULT NULL,
  `month` int NULL DEFAULT NULL,
  `salary` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `fk_sal_pid`(`person_id`) USING BTREE,
  CONSTRAINT `fk_sal_pid` FOREIGN KEY (`person_id`) REFERENCES `person` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of salary
-- ----------------------------
INSERT INTO `salary` VALUES (1, 1, 2021, 1, 9300);
INSERT INTO `salary` VALUES (2, 1, 2021, 2, 6900);
INSERT INTO `salary` VALUES (3, 1, 2021, 3, 9600);
INSERT INTO `salary` VALUES (4, 1, 2021, 4, 7500);
INSERT INTO `salary` VALUES (5, 1, 2021, 5, 8400);
INSERT INTO `salary` VALUES (6, 2, 2021, 1, 7500);
INSERT INTO `salary` VALUES (7, 2, 2021, 2, 7500);
INSERT INTO `salary` VALUES (8, 2, 2021, 3, 6900);
INSERT INTO `salary` VALUES (9, 2, 2021, 4, 10200);
INSERT INTO `salary` VALUES (10, 2, 2021, 5, 6600);
INSERT INTO `salary` VALUES (11, 3, 2021, 1, 9900);
INSERT INTO `salary` VALUES (12, 3, 2021, 2, 8700);
INSERT INTO `salary` VALUES (13, 3, 2021, 3, 7500);
INSERT INTO `salary` VALUES (14, 3, 2021, 4, 7500);
INSERT INTO `salary` VALUES (15, 3, 2021, 5, 7500);
INSERT INTO `salary` VALUES (16, 4, 2021, 1, 6900);
INSERT INTO `salary` VALUES (17, 4, 2021, 2, 6600);
INSERT INTO `salary` VALUES (18, 4, 2021, 3, 7500);
INSERT INTO `salary` VALUES (19, 4, 2021, 4, 6300);
INSERT INTO `salary` VALUES (20, 4, 2021, 5, 6000);
INSERT INTO `salary` VALUES (21, 5, 2021, 1, 3300);
INSERT INTO `salary` VALUES (22, 5, 2021, 2, 3300);
INSERT INTO `salary` VALUES (23, 5, 2021, 3, 3900);
INSERT INTO `salary` VALUES (24, 5, 2021, 4, 3450);
INSERT INTO `salary` VALUES (25, 5, 2021, 5, 3450);
INSERT INTO `salary` VALUES (26, 6, 2021, 1, 4800);
INSERT INTO `salary` VALUES (27, 6, 2021, 2, 4800);
INSERT INTO `salary` VALUES (28, 6, 2021, 3, 5600);
INSERT INTO `salary` VALUES (29, 6, 2021, 4, 6600);
INSERT INTO `salary` VALUES (30, 6, 2021, 5, 4600);
INSERT INTO `salary` VALUES (31, 7, 2021, 1, 5850);
INSERT INTO `salary` VALUES (32, 7, 2021, 2, 3750);
INSERT INTO `salary` VALUES (33, 7, 2021, 3, 4650);
INSERT INTO `salary` VALUES (34, 7, 2021, 4, 3750);
INSERT INTO `salary` VALUES (35, 7, 2021, 5, 3750);
INSERT INTO `salary` VALUES (36, 8, 2021, 1, 3600);
INSERT INTO `salary` VALUES (37, 8, 2021, 2, 3450);
INSERT INTO `salary` VALUES (38, 8, 2021, 3, 3900);
INSERT INTO `salary` VALUES (39, 8, 2021, 4, 4050);
INSERT INTO `salary` VALUES (40, 8, 2021, 5, 4350);
INSERT INTO `salary` VALUES (43, 7, 2021, 6, 3450);
INSERT INTO `salary` VALUES (44, 8, 2021, 6, 4800);

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `id` int NOT NULL,
  `name` char(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `passwd` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `grant_id` int NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (1, 'root', '123123', 0);
INSERT INTO `user` VALUES (2, '贺贺', '123123', 2);
INSERT INTO `user` VALUES (3, '任听寒', '123123', 1);

-- ----------------------------
-- View structure for worker_person
-- ----------------------------
DROP VIEW IF EXISTS `worker_person`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `worker_person` AS select `person`.`id` AS `id`,`person`.`name` AS `name`,`person`.`gender` AS `gender`,`person`.`telephone` AS `telephone`,`person`.`depart_id` AS `depart_id`,`person`.`job_id` AS `job_id`,`person`.`status` AS `status` from `person` where (concat(`person`.`name`,'@localhost') = user());

-- ----------------------------
-- Procedure structure for year_salary
-- ----------------------------
DROP PROCEDURE IF EXISTS `year_salary`;
delimiter ;;
CREATE PROCEDURE `year_salary`(in p_id int)
begin
if (p_id=0)
then
select person_id,year,(sum(salary)/count(*)) as salary
from salary
group by person_id,year;
else
select person_id,year,(sum(salary)/count(*)) as salary
from salary
where person_id=p_id
group by person_id,year;
end if;
end
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table person
-- ----------------------------
DROP TRIGGER IF EXISTS `update_person`;
delimiter ;;
CREATE TRIGGER `update_person` AFTER UPDATE ON `person` FOR EACH ROW begin
delete from user where new.status=0 and name=old.name;
end
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
