package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.DeviceParameters;
import com.flushbonading.cps.entity.dto.DeviceParametersDTO;
import com.flushbonading.cps.entity.dto.EquipmentSearchDTO;
import com.flushbonading.cps.entity.vo.DeviceParametersVO;
import com.flushbonading.cps.entity.vo.EquipmentDataVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-15
 */
@Mapper
public interface DeviceParametersMapper extends BaseMapper<DeviceParameters> {
    /**
     * 查询显示的数据数量
     *
     * @param search
     * @param page
     * @return
     */
    List<DeviceParametersVO> getAllDeviceParameters(EquipmentSearchDTO search, Integer page);

    /**
     * 得到总记录数
     *
     * @param search
     * @return
     */
    Integer getDeviceParametersCounts(@Param("search") EquipmentSearchDTO search);

    /**
     * 修改绑定信息
     *
     * @param equipmentId
     * @return
     */
    Integer updateDeviceParameters(@Param("equipmentId") String equipmentId);

    /**
     * 插入一条设备参数
     *
     * @param params
     * @return
     */
    Integer insertDeviceParameters(@Param("params") DeviceParametersDTO params);

    /**
     * 当前设备参数
     *
     * @return
     */
    EquipmentDataVO getEquipmentData(@Param("equipment_id") String equipment_id);
}
