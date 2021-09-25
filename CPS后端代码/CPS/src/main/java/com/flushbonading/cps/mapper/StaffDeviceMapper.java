package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.StaffDevice;
import com.flushbonading.cps.entity.dto.SearchStaffDeviceDTO;
import com.flushbonading.cps.entity.vo.StaffDeviceVO;
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
public interface StaffDeviceMapper extends BaseMapper<StaffDevice> {
    /**
     * 得到所有上班记录
     *
     * @param search
     * @param page
     * @return
     */
    List<StaffDeviceVO> getAllStaffDeviceDatas(SearchStaffDeviceDTO search, Integer page);

    /**
     * 查询总记录数
     *
     * @param search
     * @return
     */
    Integer getTotalCounts(@Param("search") SearchStaffDeviceDTO search);

    /**
     * 得到id
     *
     * @param createTime
     * @param staffNumber
     * @return
     */
    List<Integer> getStaffDeiviceIDs(@Param("createTime") String createTime, @Param("staffNumber") String staffNumber);

    /**
     * 插入一条记录
     *
     * @param equipmentId
     * @param packagingWorker
     * @param producer
     * @return
     */
    Integer insertAStaffDevice(String equipmentId, String packagingWorker, String producer);

    /**
     * 数量加一
     *
     * @param equipmentId
     * @param packagingWorker
     * @param producer
     * @return
     */
    Integer increase(String equipmentId, String packagingWorker, String producer);

}
