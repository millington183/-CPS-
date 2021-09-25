package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.StaffDevice;
import com.flushbonading.cps.entity.dto.SearchStaffDeviceDTO;
import com.flushbonading.cps.entity.vo.StaffDeviceVO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-21
 */
public interface StaffDeviceService extends IService<StaffDevice> {
    /**
     * 得到所有上班记录
     *
     * @param search
     * @param page
     * @return
     */
    List<StaffDeviceVO> getAllStaffDeviceDatas(SearchStaffDeviceDTO search, Integer page);

    /**
     * 得到记录总数
     *
     * @param search
     * @return
     */
    Integer getTotalCounts(SearchStaffDeviceDTO search);

    /**
     * 得到总页面数
     *
     * @param search
     * @return
     */
    Integer getTotalPages(SearchStaffDeviceDTO search);
    
}
