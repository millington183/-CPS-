package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.Equipment;
import com.flushbonading.cps.entity.vo.EquipmentInfoVO;
import com.flushbonading.cps.entity.vo.EquipmentNameVO;
import com.flushbonading.cps.entity.vo.MaintenanceDataVO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-09
 */
public interface EquipmentService extends IService<Equipment> {
    /**
     * 取得正在上班的工人数
     *
     * @return
     */
    Integer staffCounts();

    /**
     * 是否需要显示弹窗
     *
     * @return
     */
    Boolean maintenancePeriod();

    /**
     * 查询没有上传设备对应的相关信息
     *
     * @return List<EquipmentInfoVO>
     * @author pw
     */
    List<EquipmentInfoVO> queryEquipmentInfo();

    /**
     * 下发指令
     */
    void postDown();

    /**
     * 得到保养信息
     *
     * @return
     */
    MaintenanceDataVO getMaintenanceDataVO();

    /**
     * 设备名下拉列表
     *
     * @return
     */
    List<EquipmentNameVO> getEquipmentName();
}
