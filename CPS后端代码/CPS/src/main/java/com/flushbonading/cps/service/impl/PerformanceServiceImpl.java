package com.flushbonading.cps.service.impl;

import cn.hutool.core.lang.Validator;
import cn.hutool.core.util.PageUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.constant.Tip;
import com.flushbonading.cps.entity.Performance;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.Staff;
import com.flushbonading.cps.entity.dto.AddPerformanceDTO;
import com.flushbonading.cps.entity.dto.EditPerformanceDTO;
import com.flushbonading.cps.entity.dto.SearchPerformanceDTO;
import com.flushbonading.cps.entity.vo.PerformanceVO;
import com.flushbonading.cps.entity.vo.PersonalPerformanceVO;
import com.flushbonading.cps.mapper.PerformanceMapper;
import com.flushbonading.cps.mapper.StaffDeviceMapper;
import com.flushbonading.cps.mapper.StaffMapper;
import com.flushbonading.cps.service.PerformanceService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.text.SimpleDateFormat;
import java.util.Date;
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
public class PerformanceServiceImpl extends ServiceImpl<PerformanceMapper, Performance> implements PerformanceService {

    @Autowired
    StaffMapper staffMapper;
    @Autowired
    StaffDeviceMapper staffDeviceMapper;
    @Autowired
    PerformanceMapper performanceMapper;

    @Override
    public RespBean insertAPerformance(AddPerformanceDTO addPerformance) {
        String createTime = addPerformance.getCreateTime();
        String staffNumber = addPerformance.getStaffNumber();

        Validator.validateNotEmpty(createTime, Tip.ERROR_INPUT.content());
        Validator.validateNotEmpty(staffNumber, Tip.ERROR_INPUT.content());
        List<Integer> iDs = staffDeviceMapper.getStaffDeiviceIDs(createTime, staffNumber);
        if (iDs.size() <= 0) {
            return RespBean.error(Tip.STAFF_DEVICE_NOT_EXIST.content());
        }
        QueryWrapper<Staff> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("staff_number", staffNumber);
        Staff staff = staffMapper.selectOne(queryWrapper);
        Validator.validateNotNull(staff, Tip.STAFF_ERROR.content());

        Performance performance = performanceMapper.selectAPerformance(staffNumber, createTime);
        Validator.validateNull(performance, Tip.PERFORMANCE_EXIT.content());

        SimpleDateFormat formatter = new SimpleDateFormat("dd HH:mm:ss");
        Integer insertAPerformance = performanceMapper.insertAPerformance(addPerformance, staff.getPostId(), addPerformance.getCreateTime() + "-" + formatter.format(new Date()));

        Validator.validateNotNull(insertAPerformance, Tip.INSERT_ERROR.content());
        return RespBean.success(Tip.INSERT_SUCCESS.content());
    }

    @Override
    public List<PerformanceVO> selectAllPerformances(SearchPerformanceDTO search, Integer page) {
        List<PerformanceVO> performanceVOs = performanceMapper.selectAllPerformances(search, page);
        for (PerformanceVO performanceVO : performanceVOs) {
            performanceVO.setCreateTime(performanceVO.getCreateTime().substring(0, 7));
        }
        return performanceVOs;
    }

    @Override
    public Integer getTotalCounts(SearchPerformanceDTO search) {
        return performanceMapper.getTotalCounts(search);
    }

    @Override
    public Integer getTotalPages(SearchPerformanceDTO search) {
        return PageUtil.totalPage(getTotalCounts(search), 7);
    }

    @Override
    public RespBean deletePerformanceByID(String id) {
        Integer deletePerformanceByID = performanceMapper.deletePerformanceByID(id);
        Validator.validateNotNull(deletePerformanceByID, Tip.DELETE_ERROE.content());
        return RespBean.success(Tip.DELETE_SUCCESS.content());
    }

    @Override
    public EditPerformanceDTO selectAPerformanceByID(String id) {
        return performanceMapper.selectAPerformanceByID(id);
    }

    @Override
    public RespBean updatePerformance(EditPerformanceDTO edit) {
        Integer updatePerformance = performanceMapper.updatePerformance(edit);
        Validator.validateNotNull(updatePerformance, Tip.EDIT_ERROR.content());
        return RespBean.success(Tip.EDIT_SUCCESS.content());
    }

    @Override
    public List<PersonalPerformanceVO> getPersonalPerformanceVOs(String year, String staffNumber, Integer page) {
        QueryWrapper<Staff> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("staff_number", staffNumber);
        Staff staff = staffMapper.selectOne(queryWrapper);

        List<PersonalPerformanceVO> vos = performanceMapper.getPersonalPerformanceVOs(year, staffNumber, staff.getPostId(), page);
        for (PersonalPerformanceVO personalPerformanceVO : vos) {
            personalPerformanceVO.setCreateTime(personalPerformanceVO.getCreateTime().substring(0, 7));
        }
        return vos;
    }

    @Override
    public Integer getPersonalPerformanceTotalCounts(String year, String staffNumber) {
        return performanceMapper.getPersonalPerformanceTotalCounts(year, staffNumber);
    }

    @Override
    public Integer getPersonalPerformanceTotalPages(String year, String staffNumber) {
        return PageUtil.totalPage(getPersonalPerformanceTotalCounts(year, staffNumber), 6);
    }


}
