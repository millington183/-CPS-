package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.MaintenanceRecord;
import com.flushbonading.cps.entity.dto.AddRecordDTO;
import com.flushbonading.cps.entity.dto.MaintenanceRecordDTO;
import com.flushbonading.cps.entity.vo.MaintenanceRecordVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-18
 */
@Mapper
public interface MaintenanceRecordMapper extends BaseMapper<MaintenanceRecord> {
    /**
     * 得到所有保养记录
     *
     * @param search
     * @param page
     * @return
     */
    List<MaintenanceRecordVO> getAllMaintenanceRecord(MaintenanceRecordDTO search, Integer page);

    /**
     * 增加一条记录
     *
     * @param maintenanceRecord
     * @return
     */
    Integer addAMaintenanceRecord(@Param("maintenanceRecord") AddRecordDTO maintenanceRecord);

    /**
     * 得到保养记录的个数
     *
     * @param search
     * @return
     */
    Integer getRecordCounts(@Param("search") MaintenanceRecordDTO search);

    /**
     * 删除一条记录
     *
     * @param id
     * @return
     */
    Integer deleteARecordById(String id);

    /**
     * 修改一条记录
     *
     * @param updateRecord
     * @param id
     * @return
     */
    Integer updateARecord(AddRecordDTO updateRecord, Integer id);

    /**
     * 得到最近的一条保养时间
     *
     * @param equipmentId
     * @return
     */
    String recentTimeByEquipmentId(String equipmentId);

}
