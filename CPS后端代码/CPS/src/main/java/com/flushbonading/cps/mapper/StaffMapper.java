package com.flushbonading.cps.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.flushbonading.cps.entity.Staff;
import com.flushbonading.cps.entity.dto.AddStaffDTO;
import com.flushbonading.cps.entity.dto.PersonalInformationDTO;
import com.flushbonading.cps.entity.dto.SearchUsersDTO;
import com.flushbonading.cps.entity.vo.StaffVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * Mapper 接口
 * </p>
 *
 * @author zyx
 * @since 2021-06-12
 */
@Mapper
public interface StaffMapper extends BaseMapper<Staff> {
    /**
     * 根据工号来查询用户的具体信息
     *
     * @param staffNumber 工号
     * @return 用户的具体信息
     */
    PersonalInformationDTO selectInformationByStaffNumber(String staffNumber);

    /**
     * 得到所有员工信息
     *
     * @return
     */
    List<StaffVO> getAllStaffMessage(SearchUsersDTO search, Integer page);

    /**
     * 得到所有员工的总数
     *
     * @param search
     * @return
     */
    Integer getStaffCounts(@Param("search") SearchUsersDTO search);

    /**
     * 删除员工
     *
     * @param staffNumber
     * @return
     */
    Integer deleteStaff(String staffNumber);

    /**
     * 添加一个员工
     *
     * @param addStaff
     * @return
     */
    Integer addAStaff(@Param("addStaff") AddStaffDTO addStaff);

    /**
     * 修改个人信息
     *
     * @param personalInformation
     * @return
     */
    Integer updatePersonalInformation(@Param("personalInformation") PersonalInformationDTO personalInformation);

    /**
     * 通过id修改员工信息
     *
     * @param edit
     * @return
     */
    Integer updateSatffByStaffNumber(@Param("edit") AddStaffDTO edit);
}
