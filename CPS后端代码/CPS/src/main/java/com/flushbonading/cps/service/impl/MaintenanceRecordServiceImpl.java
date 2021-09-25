package com.flushbonading.cps.service.impl;

import cn.hutool.core.lang.Validator;
import cn.hutool.core.util.PageUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.constant.Tip;
import com.flushbonading.cps.entity.Equipment;
import com.flushbonading.cps.entity.MaintenanceRecord;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.AddRecordDTO;
import com.flushbonading.cps.entity.dto.MaintenanceRecordDTO;
import com.flushbonading.cps.entity.vo.MaintenanceRecordVO;
import com.flushbonading.cps.mapper.EquipmentMapper;
import com.flushbonading.cps.mapper.MaintenanceRecordMapper;
import com.flushbonading.cps.service.MaintenanceRecordService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-18
 */
@Service
public class MaintenanceRecordServiceImpl extends ServiceImpl<MaintenanceRecordMapper, MaintenanceRecord> implements MaintenanceRecordService {

    @Autowired
    MaintenanceRecordMapper maintenanceRecordMapper;
    @Autowired
    EquipmentMapper equipmentMapper;

    @Override
    public List<MaintenanceRecordVO> getAllMaintenanceRecord(MaintenanceRecordDTO search, Integer page) {
        List<MaintenanceRecordVO> allRecords = maintenanceRecordMapper.getAllMaintenanceRecord(search, page);
        for (MaintenanceRecordVO record : allRecords) {
            record.setCreateTime(record.getCreateTime().substring(0, 10));
        }
        return allRecords;
    }

    @Override
    public RespBean addAMaintenanceRecord(AddRecordDTO maintenanceRecord) {
        String equipmentId = maintenanceRecord.getEquipmentId();
        Validator.validateNotEmpty(equipmentId, Tip.ERROR_INPUT.content());

        QueryWrapper<Equipment> equipmentWrapper = new QueryWrapper<>();
        equipmentWrapper.eq("equipment_id", equipmentId);
        Equipment equipment = equipmentMapper.selectOne(equipmentWrapper);
        Validator.validateNotNull(equipment, Tip.EQUIPMENT_NOT_EXIST.content());

        Integer addRecord = maintenanceRecordMapper.addAMaintenanceRecord(maintenanceRecord);
        Validator.validateNotNull(addRecord, Tip.INSERT_ERROR.content());
        return RespBean.success(Tip.INSERT_SUCCESS.content());
    }

    @Override
    public Integer getRecordCounts(MaintenanceRecordDTO search) {
        return maintenanceRecordMapper.getRecordCounts(search);
    }

    @Override
    public Integer getTotalPageCounts(MaintenanceRecordDTO search) {
        return PageUtil.totalPage(getRecordCounts(search), 7);
    }

    @Override
    public RespBean deleteARecordById(String id) {
        Integer record = maintenanceRecordMapper.deleteARecordById(id);
        Validator.validateNotNull(record, Tip.DELETE_ERROE.content());
        return RespBean.success(Tip.DELETE_SUCCESS.content());
    }

    @Override
    public RespBean updateARecord(AddRecordDTO updateRecord, Integer id) {
        String name = updateRecord.getName();
        Validator.validateNotEmpty(name, Tip.ERROR_INPUT.content());
        String createTime = updateRecord.getCreateTime();
        Validator.validateNotEmpty(createTime, Tip.ERROR_INPUT.name());

        Integer record = maintenanceRecordMapper.updateARecord(updateRecord, id);
        Validator.validateNotNull(record, Tip.EDIT_ERROR.content());
        return RespBean.success(Tip.EDIT_SUCCESS.content());
    }
}
