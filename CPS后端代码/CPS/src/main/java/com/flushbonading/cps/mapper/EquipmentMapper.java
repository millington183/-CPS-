package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Equipment;
import com.flushbonading.cps.entity.dto.EquipmentDTO;
import com.flushbonading.cps.entity.dto.PostDownMaintenanceDTO;
import com.flushbonading.cps.entity.vo.EquipmentInfoVO;
import com.flushbonading.cps.entity.vo.EquipmentNameVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
@Mapper
public interface EquipmentMapper extends BaseMapper<Equipment> {
    /**
     * 拿到保养日期
     *
     * @return
     */
    List<EquipmentDTO> getMaintenancePeriod();

    /**
     * 查询没有上传设备对应的相关信息
     *
     * @return List<EquipmentInfoVO>
     * @author pw
     */
    List<EquipmentInfoVO> queryEquipmentInfo();


    /**
     * 更新人员
     *
     * @param equipmentId
     * @param packagingWorker
     * @param producer
     * @return
     */
    Integer updatePeople(String equipmentId, String packagingWorker, String producer);

    /**
     * 增加一产品
     *
     * @param equipmentId
     * @return
     */
    Integer increase(String equipmentId);

    /**
     * 修改保养时间
     *
     * @param maintenancePeriod
     * @param equipmentId
     * @return
     */
    Integer updateMaintenancePeriod(@Param("maintenancePeriod") String maintenancePeriod, @Param("equipmentId") String equipmentId);

    /**
     * 下发设备所需信息
     *
     * @return
     */
    List<PostDownMaintenanceDTO> getPostDownMaintenanceDTO();

    /**
     * 设备名下拉列表
     *
     * @return
     */
    List<EquipmentNameVO> getEquipmentName();
}
