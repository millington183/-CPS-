package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.Staff;
import com.flushbonading.cps.entity.dto.AddStaffDTO;
import com.flushbonading.cps.entity.dto.PersonalInformationDTO;
import com.flushbonading.cps.entity.dto.SearchUsersDTO;
import com.flushbonading.cps.entity.vo.StaffVO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-12
 */
public interface StaffService extends IService<Staff> {
    /**
     * 通过工号查询姓名
     *
     * @param staffNumber 工号
     * @return 姓名
     */
    String getNameByStaffNumber(String staffNumber);

    /**
     * 通过工号查询详细信息
     *
     * @param staffNumber 工号
     * @return 返回存有详细信息的对象
     */
    PersonalInformationDTO selectInformationByStaffNumber(String staffNumber);


    /**
     * 得到所有员工的信息
     *
     * @param search    搜索内容对象
     * @param pageIndex 页面索引
     * @return
     */
    List<StaffVO> getAllStaffMessage(SearchUsersDTO search, Integer pageIndex);

    /**
     * 得到所有员工的总数
     *
     * @param search
     * @return
     */
    Integer getStaffCounts(SearchUsersDTO search);

    /**
     * 总页数
     *
     * @return
     */
    Integer getTotalPage(SearchUsersDTO search);

    /**
     * 删除一个员工
     *
     * @param staffNumber
     * @return
     */
    RespBean deleteStaff(String staffNumber);

    /**
     * 插入一个员工
     *
     * @param addStaff
     * @return
     */
    RespBean insertAStaff(AddStaffDTO addStaff);

    /**
     * 更新个人信息
     *
     * @param personalInformation
     * @return
     */
    RespBean updatePersonalInformation(PersonalInformationDTO personalInformation);

    /**
     * 修改某个员工的信息
     *
     * @param edit
     * @return
     */
    RespBean updateSatffByStaffNumber(AddStaffDTO edit);
}
