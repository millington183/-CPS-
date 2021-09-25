package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Performance;
import com.flushbonading.cps.entity.dto.AddPerformanceDTO;
import com.flushbonading.cps.entity.dto.EditPerformanceDTO;
import com.flushbonading.cps.entity.dto.SearchPerformanceDTO;
import com.flushbonading.cps.entity.vo.PerformanceVO;
import com.flushbonading.cps.entity.vo.PersonalPerformanceVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-21
 */
@Mapper
public interface PerformanceMapper extends BaseMapper<Performance> {

    /**
     * 插入一条考勤记录
     *
     * @param addPerformance
     * @param postId
     * @param createTime
     * @return
     */
    Integer insertAPerformance(AddPerformanceDTO addPerformance, Integer postId, String createTime);

    /**
     * 通过时间和工号查询某条记录
     *
     * @param staffNumber
     * @param createTime
     * @return
     */
    Performance selectAPerformance(String staffNumber, String createTime);

    /**
     * 得到所有绩效信息
     *
     * @param search
     * @param page
     * @return
     */
    List<PerformanceVO> selectAllPerformances(@Param("search") SearchPerformanceDTO search, Integer page);

    /**
     * 得到总数
     *
     * @param search
     * @return
     */
    Integer getTotalCounts(@Param("search") SearchPerformanceDTO search);

    /**
     * 根据id删除
     *
     * @param id
     * @return
     */
    Integer deletePerformanceByID(String id);

    /**
     * 查询单个信息
     *
     * @param id
     * @return
     */
    EditPerformanceDTO selectAPerformanceByID(String id);

    /**
     * 更新数据
     *
     * @param edit
     * @return
     */
    Integer updatePerformance(@Param("edit") EditPerformanceDTO edit);


    /**
     * 得到个人绩效
     *
     * @param year
     * @param staffNumber
     * @param postId
     * @param page
     * @return
     */
    List<PersonalPerformanceVO> getPersonalPerformanceVOs(String year, String staffNumber, Integer postId, Integer page);

    /**
     * 拿到所有个人绩效数量
     *
     * @param year
     * @param staffNumber
     * @return
     */
    Integer getPersonalPerformanceTotalCounts(String year, String staffNumber);

}
