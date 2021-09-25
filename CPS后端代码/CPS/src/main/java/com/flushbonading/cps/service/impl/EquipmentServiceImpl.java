package com.flushbonading.cps.service.impl;

import cn.hutool.core.date.DateUnit;
import cn.hutool.core.date.DateUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.entity.Equipment;
import com.flushbonading.cps.entity.dto.EquipmentDTO;
import com.flushbonading.cps.entity.dto.PostDownMaintenanceDTO;
import com.flushbonading.cps.entity.vo.EquipmentInfoVO;
import com.flushbonading.cps.entity.vo.EquipmentNameVO;
import com.flushbonading.cps.entity.vo.MaintenanceDataVO;
import com.flushbonading.cps.mapper.EquipmentMapper;
import com.flushbonading.cps.mapper.MaintenanceRecordMapper;
import com.flushbonading.cps.service.EquipmentService;
import com.flushbonading.cps.util.OKHttpUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;

import java.time.ZoneId;
import java.util.Date;
import java.util.List;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Service
public class EquipmentServiceImpl extends ServiceImpl<EquipmentMapper, Equipment> implements EquipmentService {

    /**
     * 设备映射器
     */
    @Autowired
    OKHttpUtil okHttpUtil;
    @Autowired
    EquipmentMapper equipmentMapper;
    @Autowired
    MaintenanceRecordMapper maintenanceRecordMapper;

    /**
     * 取得正在上班的工人数
     *
     * @return
     */
    @Override
    public Integer staffCounts() {
        //查询包装人员的数量
        QueryWrapper<Equipment> wrapper = new QueryWrapper<>();
        wrapper.isNotNull("packaging_worker");
        Integer packagingWorksCounts = equipmentMapper.selectCount(wrapper);
        wrapper.isNotNull("producer");
        Integer producerCounts = equipmentMapper.selectCount(wrapper);
        return new Integer(packagingWorksCounts.intValue() + producerCounts.intValue());
    }

    @Override
    public Boolean maintenancePeriod() {
        List<EquipmentDTO> equipmentDTOs = equipmentMapper.getMaintenancePeriod();
        for (EquipmentDTO equipmentDTO : equipmentDTOs) {
            if (maintenanceRecordMapper.recentTimeByEquipmentId(equipmentDTO.getEquipmentId()) != null) {
                java.lang.String oldTime = maintenanceRecordMapper.recentTimeByEquipmentId(equipmentDTO.getEquipmentId()).substring(0, 10);
                java.lang.String newTime = equipmentDTO.getMaintenancePeriod().substring(0, 10);
                Date startTime = new Date(Integer.parseInt(oldTime.substring(0, 4)), Integer.parseInt(oldTime.substring(5, 7)), Integer.parseInt(oldTime.substring(8, 10)));
                Date endTime = new Date(Integer.parseInt(newTime.substring(0, 4)), Integer.parseInt(newTime.substring(5, 7)), Integer.parseInt(newTime.substring(8, 10)));
                long betweenDay = DateUtil.betweenDay(startTime, endTime, false);
                System.out.println(betweenDay);
                if (betweenDay <= 7) {
                    return true;
                }
            }
        }
        return false;
    }

    @Override
    public List<EquipmentInfoVO> queryEquipmentInfo() {
        List<EquipmentInfoVO> equipmentInfo = equipmentMapper.queryEquipmentInfo();
        for (EquipmentInfoVO equipmentInfoVO : equipmentInfo) {
            java.lang.String date = equipmentInfoVO.getMaintenancePeriod();
            String substring = date.substring(0, 10);
            equipmentInfoVO.setMaintenancePeriod(substring);
        }
        return equipmentInfo;
    }

    @Scheduled(cron = "0 0/2 * * * ?")
    @Override
    public void postDown() {
//        System.out.println("执行了保养定时任务");
//        okHttpUtil.postData("M,1,0,N");
//        List<PostDownMaintenanceDTO> postDownMaintenanceDTO = equipmentMapper.getPostDownMaintenanceDTO();
//        Date now = new Date();
//        for (PostDownMaintenanceDTO postDownMaintenance : postDownMaintenanceDTO) {
//            //System.out.println(postDownMaintenance.getEquipmentId());
//            Date maintenanceDate = Date.from(postDownMaintenance.getMaintenancePeriod().atZone(ZoneId.systemDefault()).toInstant());
//            String data = "M," + postDownMaintenance.getEquipmentId() + ",";
//            if (maintenanceDate.before(now)) {
//                System.out.println("下发了超过保养日期");
//                data = data + "0,N";
//                okHttpUtil.postData(data);
//                continue;
//            }
//            long betweenDay = DateUtil.between(now, maintenanceDate, DateUnit.DAY);
//            if (betweenDay < 7 && betweenDay >= 1) {
//                System.out.println("下发了距离还有" + betweenDay + "天");
//                data = data + betweenDay + ",D";
//                okHttpUtil.postData(data);
//                continue;
//            }
//            long betweenHour = DateUtil.between(now, maintenanceDate, DateUnit.HOUR);
//            if (betweenHour < 24 && betweenHour >= 1) {
//                System.out.println("下发了距离还有" + betweenHour + "小时");
//                data = data + betweenHour + ",H";
//                okHttpUtil.postData(data);
//                continue;
//            }
//
//            long betweenMinute = DateUtil.between(now, maintenanceDate, DateUnit.MINUTE);
//            if (betweenMinute < 60 && betweenMinute >= 1) {
//                System.out.println("下发了距离还有" + betweenHour + "分");
//                data = data + betweenMinute + ",H";
//                okHttpUtil.postData(data);
//                continue;
//            }
//
//            long betweenSecond = DateUtil.between(now, maintenanceDate, DateUnit.SECOND);
//            if (betweenSecond < 60 && betweenSecond >= 0) {
//                System.out.println("下发了距离还有" + betweenSecond + "秒");
//                data = data + betweenMinute + ",S";
//                okHttpUtil.postData(data);
//                continue;
//            }
//        }
    }

    @Override
    public MaintenanceDataVO getMaintenanceDataVO() {
        List<PostDownMaintenanceDTO> postDownMaintenanceDTO = equipmentMapper.getPostDownMaintenanceDTO();
        String month = "";
        String week = "";
        String late = "";
        Date now = new Date();
        for (PostDownMaintenanceDTO postDownMaintenance : postDownMaintenanceDTO) {
            Date maintenanceDate = Date.from(postDownMaintenance.getMaintenancePeriod().atZone(ZoneId.systemDefault()).toInstant());
            if (maintenanceDate.before(now)) {
                late = late + postDownMaintenance.getEquipmentId() + ",";
                continue;
            }
            long betweenDay = DateUtil.between(now, maintenanceDate, DateUnit.DAY);
            if (betweenDay <= 30) {
                month = month + postDownMaintenance.getEquipmentId() + ",";
                if (betweenDay <= 7 && betweenDay >= 0) {
                    month = month + postDownMaintenance.getEquipmentId() + ",";
                }
            }
        }
        if (month.length() > 0) {
            month = month.substring(0, month.length() - 1);
        }
        if (week.length() > 0) {
            week = week.substring(0, week.length() - 1);
        }
        if (late.length() > 0) {
            late = late.substring(0, late.length() - 1);
        }
        MaintenanceDataVO dataVO = MaintenanceDataVO.builder()
                .late(late)
                .month(month)
                .week(week)
                .build();
        return dataVO;
    }

    @Override
    public List<EquipmentNameVO> getEquipmentName() {
        return equipmentMapper.getEquipmentName();
    }
}