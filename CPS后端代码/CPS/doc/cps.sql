use cps;

-- 部门表
create table `t_department`(
    `id` int(3) not null auto_increment comment '部门id号',
    `department_name` varchar(50) not null unique comment '部门名',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    PRIMARY KEY (`id`) USING BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 员工表
create table `t_staff`(
    `id` int(3) not null auto_increment comment '员工id',
    `staff_number` varchar(15) not null unique comment '员工工号',
    `name` varchar(20) not null comment '员工名',
    `gender` varchar(2) not null comment '性别',
    `department_id` int(3) not null comment '部门id',
    `id_card` varchar(18) not null unique comment '身份证号',
    `phone` varchar(11) not null unique comment '手机',
    `post_id` int(4) not null comment '职务id',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE ,
    index (`department_id`) using BTREE ,
    index (`post_id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 职务表
create table `t_post`(
    `id` int(4) not null auto_increment comment '职务id号',
    `post_name` varchar(50) not null unique comment '职务名',
    `base_wage` int(6) not null comment '基础工资',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 部门职务表
create table `t_department_post`(
    `id` int(4) not null auto_increment comment '部门职务id',
    `department_id` int(3) not null comment '部门id',
    `post_id` int(3) not null unique comment '职务id',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE ,
    index (`department_id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;


-- 绩效表
create table `t_performance`(
        `id` int(4) not null auto_increment comment '绩效id',
        `staff_number` varchar(15) not null comment '工号',
        `year` int(4) not null comment '年',
        `month` int(2) not null comment '月',
        `counts` bigint not null comment '当月生产总数',
        `number_of_work` int(3) not null comment '上班次数',
        `number_of_leave`int(3) comment '请假次数',
        `absenteeism` int(3) comment '缺勤次数',
        `number_of_late` int(3) comment '迟到次数',
        `rewards_punishments` int(6) not null comment '奖惩金额',
        `total_wage` int(6) comment '总工资',
        `remark` text comment '备注',
        `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
        `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
        primary key (`id`) using BTREE ,
        index (`staff_number`) using BTREE ,
        index (`year`) using BTREE ,
        index (`month`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;
alter table t_performance add column `work_time` TIMESTAMP(0) comment '工作时长';


-- 学历表
create table `t_education_background`(
    `id` int(3) not null auto_increment comment '学历id号',
    `education_background` varchar(50) not null unique comment '学历名',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;


-- 用户表
create table `t_user`(
    `id` int(4) auto_increment not null comment '用户id',
    `staff_number` varchar(15) not null unique comment '工号',
    `password` varchar(32) not null comment '密码',
    `salt` varchar(6) not null comment '盐值',
    `role_id` int(2) not null comment '角色id',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE ,
    index (`role_id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 角色
create table `t_role`(
    `id` int(2) not null auto_increment comment 'id号',
    `role_id` int(2) not null unique comment '角色id',
    `role_name` varchar(15) not null unique comment '角色名',
    `remark` text comment '备注',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 菜单表
create table `t_menu`(
    `id` int(2) not null auto_increment comment 'id号',
    `menu_id` int(5) not null unique comment '菜单id',
    `parent` int(5) not null comment '父菜单id',
    `menu_name` varchar(15) not null comment '菜单名',
    `icon` varchar(50) not null comment '菜单icon',
    `path` varchar(50) comment '跳转的路径',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE ,
    index (`parent`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 菜单角色表
create table `t_role_menu`(
    `id` int(2) not null auto_increment comment 'id号',
    `role_id` int(2) not null comment '角色id',
    `menu_id` int(5) not null comment '菜单id',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE ,
    index (`role_id`) using BTREE ,
    index (`menu_id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 设备表
drop table t_equipment;
create table `t_equipment`(
    `id` int(2) not null auto_increment comment 'id号',
    `equipment_id` int(2) not null comment '设备号id',
    `equipment_name` varchar(20) not null comment '设备名',
    `packaging_worker` varchar(15) comment '包装人员工号',
    `producer` varchar(15) comment '压型人员工号',
    `maintenance_period` int(4) not null comment '保养周期',
    `counts` bigint not null default 0 comment '制作个数',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE ,
    index (`equipment_id`) using BTREE ,
    index (`packaging_worker`) using BTREE ,
    index (`producer`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 模型表
create table `t_model`(
    `id` int(2) not null auto_increment comment 'id号',
    `model_number` varchar(20) not null unique comment '模型号',
    `counts` bigint not null comment '总个数',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;


-- 设备参数
drop table `t_device_parameters`;
create table `t_device_parameters`(
    `id` int(2) not null auto_increment comment 'id号',
    `equipment_id` int(2) not null comment '设备号id',
    `pressing_pressure` double(7,5) not null comment '压制压力',
    `dwell_pressure` double(7,5) not null comment '保压压力',
    `current_demagnetization` Double(4,1) not null comment '退磁电流',
    `current_magnetization` Double(5,1) not null comment '充磁电流',
    `Not_bind` tinyint not null default 0 comment '是否取消绑定',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 员工设备表
create table `t_staff_device`(
    `id` int(2) not null auto_increment comment 'id号',
    `equipment_id` int(2) not null comment '设备号id',
    `packaging_worker` varchar(15) not null comment '包装人员工号',
    `producer` varchar(15) not null comment '压型人员工号',
    `counts` bigint comment '制作的总数',
    `work_time` timestamp(0) comment '工作时长',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE ,
    index (`packaging_worker`) using BTREE ,
    index (`producer`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 每日每时刻生产数量统计表
create table `t_diary`(
    `id` int(2) not null auto_increment comment 'id号',
    `equipment_id` int(2) not null comment '设备号id',
    `time_id` int(2) not null comment '时间段id',
    `counts` bigint not null default 0 comment '生产数量',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE ,
    index (`equipment_id`) using BTREE ,
    index (`time_id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;


-- 物料表
create table `t_material`(
    `id` int(2) not null auto_increment comment 'id号',
    `material_id` varchar(20) not null unique comment '物料牌号',
    `al` Double(4,2) comment '铝的比例',
    `fe` Double(4,2) comment '铁的比例',
    `b`  Double(4,2) comment '硼的比例',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 产品表
drop table `t_product`;
create table `t_product`(
    `id` bigint not null auto_increment comment 'id号',
    `material_id` varchar(20) not null comment '物料牌号',
    `equipment_id` int(2) not null comment '设备id',
    `model_number` varchar(20) not null comment '模型号',
    `pressing_pressure` double(7,5) not null comment '压制压力',
    `dwell_pressure` double(7,5) not null comment '保压压力',
    `current_demagnetization` Double(4,1) not null comment '退磁电流',
    `current_magnetization` Double(5,1) not null comment '充磁电流',
    `weight` Double(5,1) comment '重量',
    `size` Double(6,3) comment  '尺寸',
    `said_powder_time` Int(1) comment '称粉计时',
    `result` int(2) not null default 0 comment '结果',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 环境表
create table `t_environment`(
    `id` Int(2) not null auto_increment comment 'id号',
    `temperature` Double(5,2) not null comment '温度',
    `humidity` Double(4,2) not null comment '湿度',
    `dust` Double(4,2) not null comment '粉尘浓度',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

create table `t_maintenance_record`(
    `id` Int(2) not null auto_increment comment 'id号',
    `equipment_id` Int(2) not null comment '设备id',
    `name` Varchar(20) not null comment '保养人',
    `year` int(4) not null comment '年',
    `month` int(2) not null comment '月',
    `day` int(2) not null comment '日',
    `update_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) ON UPDATE CURRENT_TIMESTAMP(0) COMMENT '更新时间',
    `create_time` TIMESTAMP(0) NOT NULL DEFAULT CURRENT_TIMESTAMP(0) COMMENT '创建时间',
    primary key (`id`) using BTREE ,
    index (`year`) using BTREE ,
    index (`month`) using BTREE ,
    index (`day`) using BTREE
)ENGINE = INNODB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci;

-- 在设备表中创建触发器(在增加设备时候触发)
DELIMITER $
CREATE TRIGGER diary AFTER INSERT ON `t_equipment` FOR EACH ROW
BEGIN
    DECLARE equipment int(2);
    SET equipment = (select equipment_id from t_equipment order by id DESC limit 1);
    insert into t_diary(`equipment_id`,`time_id`)
    values (equipment,1),(equipment,2),(equipment,3),(equipment,4),(equipment,5),(equipment,6);
END $
DELIMITER ;

-- 初始化侧边栏数据
insert into t_menu(`menu_id`,`parent`,`menu_name`,`icon`,`path`)
values
(1,0,'系统管理','el-icon-setting','sys'),(11,1,'用户管理','el-icon-user','roleManagement'),(12,1,'角色管理','el-icon-s-custom','jurisdictionManagement'),
(2,0,'员工管理','el-icon-menu','people'),(21,2,'人员管理','el-icon-user','personManagement'),(22,2,'绩效考核','el-icon-tickets','performanceAppraisal'),
(3,0,'生产管理',' el-icon-location','production'),(31,3,'设备显示','el-icon-odometer','equipmentManagement'),(32,3,'设备数据','el-icon-coin','equipmentData'),(33,3,'生产数据','el-icon-s-data','productionData'),(34,3,'设备保养','el-icon-brush','equipmentUpkeep'),(35,3,'物料管理','el-icon-notebook-1','batchingManagement'),
(4,0,'个人绩效','el-icon-s-check','personPerformance'),
(5,0,'个人信息','el-icon-user-solid','information');

-- 初始化学历表
insert into t_education_background(`education_background`)
values
('小学'),('初中'),('高中'),('本科'),('研究生'),('博士');