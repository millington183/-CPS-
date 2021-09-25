package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.MaintenanceRecord;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.AddRecordDTO;
import com.flushbonading.cps.entity.dto.MaintenanceRecordDTO;
import com.flushbonading.cps.entity.vo.MaintenanceRecordVO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-18
 */
public interface MaintenanceRecordService extends IService<MaintenanceRecord> {
    /**
     * 得到所有保养记录
     *
     * @param search
     * @param page
     * @return
     */
    List<MaintenanceRecordVO> getAllMaintenanceRecord(MaintenanceRecordDTO search, Integer page);

    /**
     * 插入一条数据
     *
     * @param maintenanceRecord
     * @return
     */
    RespBean addAMaintenanceRecord(AddRecordDTO maintenanceRecord);

    /**
     * 得到总记录数
     *
     * @param search
     * @return
     */
    Integer getRecordCounts(MaintenanceRecordDTO search);

    /**
     * 得到总页面数
     *
     * @param search
     * @return
     */
    Integer getTotalPageCounts(MaintenanceRecordDTO search);

    /**
     * 删除一条记录
     *
     * @param id
     * @return
     */
    RespBean deleteARecordById(String id);

    /**
     * 修改一条记录
     *
     * @param updateRecord
     * @param id
     * @return
     */
    RespBean updateARecord(AddRecordDTO updateRecord, Integer id);
    
}
