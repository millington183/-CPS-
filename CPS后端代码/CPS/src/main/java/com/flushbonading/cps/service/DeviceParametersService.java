package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.DeviceParameters;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.EquipmentSearchDTO;
import com.flushbonading.cps.entity.vo.DeviceParametersVO;
import com.flushbonading.cps.entity.vo.EquipmentDataVO;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-15
 */
public interface DeviceParametersService extends IService<DeviceParameters> {
    /**
     * 查询显示的数据数量
     *
     * @param search
     * @param pageIndex
     * @return
     */
    List<DeviceParametersVO> getAllDeviceParameters(EquipmentSearchDTO search, Integer pageIndex);

    /**
     * 得到总记录数
     *
     * @param search
     * @return
     */
    Integer getDeviceParametersCounts(EquipmentSearchDTO search);

    /**
     * 得到总页数
     *
     * @param search
     * @return
     */
    Integer totalPage(EquipmentSearchDTO search);

    /**
     * 更新绑定信息
     *
     * @param equipmentId
     * @return
     */
    RespBean updateDeviceParameters(String equipmentId);

    /**
     * 当前数据
     *
     * @param equipment_id
     * @return
     */
    EquipmentDataVO getEquipmentData(@Param("equipment_id") String equipment_id);
}
