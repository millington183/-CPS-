package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.Performance;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.dto.AddPerformanceDTO;
import com.flushbonading.cps.entity.dto.EditPerformanceDTO;
import com.flushbonading.cps.entity.dto.SearchPerformanceDTO;
import com.flushbonading.cps.entity.vo.PerformanceVO;
import com.flushbonading.cps.entity.vo.PersonalPerformanceVO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-21
 */
public interface PerformanceService extends IService<Performance> {
    /**
     * 插入一条考勤记录
     *
     * @param addPerformance
     * @return
     */
    RespBean insertAPerformance(AddPerformanceDTO addPerformance);

    /**
     * 得到所有绩效信息
     *
     * @param search
     * @param page
     * @return
     */
    List<PerformanceVO> selectAllPerformances(SearchPerformanceDTO search, Integer page);

    /**
     * 得到数据总数
     *
     * @param search
     * @return
     */
    Integer getTotalCounts(SearchPerformanceDTO search);

    /**
     * @param search
     * @return
     */
    Integer getTotalPages(SearchPerformanceDTO search);

    /**
     * 根据id删除绩效
     *
     * @param id
     * @return
     */
    RespBean deletePerformanceByID(String id);

    /**
     * 查询单个绩效
     *
     * @param id
     * @return
     */
    EditPerformanceDTO selectAPerformanceByID(String id);

    /**
     * 修改绩效
     *
     * @param edit
     * @return
     */
    RespBean updatePerformance(EditPerformanceDTO edit);

    /**
     * 得到所有个人绩效
     *
     * @param year
     * @param staffNumber
     * @param page
     * @return
     */
    List<PersonalPerformanceVO> getPersonalPerformanceVOs(String year, String staffNumber, Integer page);

    /**
     * 得到所有个人绩效数
     *
     * @param year
     * @param staffNumber
     * @return
     */
    Integer getPersonalPerformanceTotalCounts(String year, String staffNumber);

    /**
     * 得到页面总数
     *
     * @param year
     * @param staffNumber
     * @return
     */
    Integer getPersonalPerformanceTotalPages(String year, String staffNumber);
}
