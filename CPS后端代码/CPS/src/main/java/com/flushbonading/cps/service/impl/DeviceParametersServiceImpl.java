package com.flushbonading.cps.service.impl;

import cn.hutool.core.lang.Validator;
import cn.hutool.core.util.PageUtil;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.constant.Tip;
import com.flushbonading.cps.entity.DeviceParameters;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.EquipmentSearchDTO;
import com.flushbonading.cps.entity.vo.DeviceParametersVO;
import com.flushbonading.cps.entity.vo.EquipmentDataVO;
import com.flushbonading.cps.mapper.DeviceParametersMapper;
import com.flushbonading.cps.service.DeviceParametersService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-15
 */
@Service
public class DeviceParametersServiceImpl extends ServiceImpl<DeviceParametersMapper, DeviceParameters> implements DeviceParametersService {

    @Autowired
    DeviceParametersMapper deviceParametersMapper;

    @Override
    public List<DeviceParametersVO> getAllDeviceParameters(EquipmentSearchDTO search, Integer pageIndex) {
        return deviceParametersMapper.getAllDeviceParameters(search, pageIndex);
    }

    @Override
    public Integer getDeviceParametersCounts(EquipmentSearchDTO search) {
        return deviceParametersMapper.getDeviceParametersCounts(search);
    }

    @Override
    public Integer totalPage(EquipmentSearchDTO search) {
        return PageUtil.totalPage(getDeviceParametersCounts(search), 7);
    }

    @Override
    public RespBean updateDeviceParameters(String equipmentId) {
        Integer deviceParameters = deviceParametersMapper.updateDeviceParameters(equipmentId);
        Validator.validateNotNull(deviceParameters, Tip.EDIT_ERROR.content());
        return RespBean.success(Tip.EDIT_SUCCESS.content());
    }

    @Override
    public EquipmentDataVO getEquipmentData(String equipment_id) {
        return deviceParametersMapper.getEquipmentData(equipment_id);
    }
}
