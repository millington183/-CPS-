package com.flushbonading.cps.service.impl;

import cn.hutool.core.util.PageUtil;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.entity.StaffDevice;
import com.flushbonading.cps.entity.dto.SearchStaffDeviceDTO;
import com.flushbonading.cps.entity.vo.StaffDeviceVO;
import com.flushbonading.cps.mapper.StaffDeviceMapper;
import com.flushbonading.cps.mapper.StaffMapper;
import com.flushbonading.cps.service.StaffDeviceService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-21
 */
@Service
public class StaffDeviceServiceImpl extends ServiceImpl<StaffDeviceMapper, StaffDevice> implements StaffDeviceService {

    @Autowired
    StaffDeviceMapper staffDeviceMapper;
    @Autowired
    StaffMapper staffMapper;

    @Override
    public List<StaffDeviceVO> getAllStaffDeviceDatas(SearchStaffDeviceDTO search, Integer page) {
        return staffDeviceMapper.getAllStaffDeviceDatas(search, page);
    }

    @Override
    public Integer getTotalCounts(SearchStaffDeviceDTO search) {
        return staffDeviceMapper.getTotalCounts(search);
    }

    @Override
    public Integer getTotalPages(SearchStaffDeviceDTO search) {
        return PageUtil.totalPage(getTotalCounts(search), 7);
    }
}
