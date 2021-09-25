package com.flushbonading.cps.service.impl;

import cn.hutool.core.lang.Validator;
import cn.hutool.core.util.PageUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.constant.Gender;
import com.flushbonading.cps.constant.Tip;
import com.flushbonading.cps.entity.DepartmentPost;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.Staff;
import com.flushbonading.cps.entity.dto.AddStaffDTO;
import com.flushbonading.cps.entity.dto.PersonalInformationDTO;
import com.flushbonading.cps.entity.dto.SearchUsersDTO;
import com.flushbonading.cps.entity.vo.StaffVO;
import com.flushbonading.cps.mapper.*;
import com.flushbonading.cps.service.StaffService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.util.Calendar;
import java.util.List;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-12
 */
@Service
public class StaffServiceImpl extends ServiceImpl<StaffMapper, Staff> implements StaffService {
    @Autowired
    StaffMapper staffMapper;
    @Autowired
    UserMapper userMapper;
    @Autowired
    DepartmentMapper departmentMapper;
    @Autowired
    PostMapper postMapper;
    @Autowired
    DepartmentPostMapper departmentPostMapper;
    @Autowired
    RedisTemplate<String, Object> redisTemplate;

    @Override
    public String getNameByStaffNumber(String staffNumber) {
        String name = (String) redisTemplate.opsForValue().get("name:" + staffNumber);
        if (name != null) {
            return name;
        }
        QueryWrapper<Staff> staffQueryWrapper = new QueryWrapper<>();
        staffQueryWrapper.select("name").eq("staff_number", staffNumber);
        Staff staff = staffMapper.selectOne(staffQueryWrapper);
        name = staff.getName();
        redisTemplate.opsForValue().set("name:" + staffNumber, name);
        return name;
    }

    @Override
    public PersonalInformationDTO selectInformationByStaffNumber(String staffNumber) {
        PersonalInformationDTO informationDTO = staffMapper.selectInformationByStaffNumber(staffNumber);

        //计算年龄
        Integer year = Integer.parseInt(informationDTO.getIdCard().substring(6, 10));
        Calendar date = Calendar.getInstance();
        Integer currentYear = Integer.parseInt(String.valueOf(date.get(Calendar.YEAR)));
        informationDTO.setAge(currentYear - year);

        return informationDTO;
    }

    @Override
    public List<StaffVO> getAllStaffMessage(SearchUsersDTO search, Integer pageIndex) {
        return staffMapper.getAllStaffMessage(search, pageIndex);
    }

    @Override
    public Integer getStaffCounts(SearchUsersDTO search) {
        return staffMapper.getStaffCounts(search);
    }

    @Override
    public Integer getTotalPage(SearchUsersDTO search) {
        return PageUtil.totalPage(getStaffCounts(search), 6);
    }

    @Override
    public RespBean deleteStaff(String staffNumber) {
        Validator.validateNotEmpty(staffNumber, Tip.ERROR_INPUT.content());
        Integer deleteStaff = staffMapper.deleteStaff(staffNumber);
        if (deleteStaff.intValue() <= 0) {
            return RespBean.error(Tip.DELETE_ERROE.content());
        }
        userMapper.deleteUser(staffNumber);
        redisTemplate.delete("name:" + staffNumber);
        return RespBean.success(Tip.DELETE_SUCCESS.content());
    }

    @Override
    public RespBean insertAStaff(AddStaffDTO addStaff) {
        //校验
        addStaffVerify(addStaff);
        Integer add = staffMapper.addAStaff(addStaff);
        Validator.validateNotNull(add, Tip.INSERT_ERROR.content());
        return RespBean.success(Tip.INSERT_SUCCESS.content());
    }

    @Override
    public RespBean updatePersonalInformation(PersonalInformationDTO personalInformation) {
        String idCard = personalInformation.getIdCard();
        String phone = personalInformation.getPhone();

        //校验
        Validator.validateNotEmpty(idCard, Tip.ERROR_INPUT.content());
        Validator.validateNotEmpty(phone, Tip.ERROR_INPUT.content());
        Validator.isMatchRegex(Validator.CITIZEN_ID.pattern(), idCard);
        Validator.isMatchRegex(Validator.MOBILE.pattern(), phone);

        //更新
        Integer updateInteger = staffMapper.updatePersonalInformation(personalInformation);

        //校验更新结果
        Validator.validateNotNull(updateInteger, Tip.EDIT_ERROR.content());

        return RespBean.success(Tip.EDIT_SUCCESS.content());
    }

    @Override
    public RespBean updateSatffByStaffNumber(AddStaffDTO edit) {
        //校验姓名
        Validator.validateNotEmpty(edit.getName(), Tip.ERROR_INPUT.content());
        //校验性别
        String gender = edit.getGender();
        if (!(gender.equals(Gender.MALE.gender()) || gender.equals(Gender.FEMALE.gender()))) {
            return RespBean.error(Tip.ERROR_INPUT.content());
        }

        //校验手机号
        Validator.isMatchRegex(Validator.MOBILE.pattern(), edit.getPhone());
        //校验身份证
        Validator.isMatchRegex(Validator.CITIZEN_ID.pattern(), edit.getIdCard());

        Integer editResult = staffMapper.updateSatffByStaffNumber(edit);
        Validator.validateNotNull(editResult, Tip.EDIT_ERROR.content());
        redisTemplate.opsForValue().set("name:" + edit.getStaffNumber(), edit.getName());
        return RespBean.success(Tip.EDIT_SUCCESS.content());
    }

    private void addStaffVerify(AddStaffDTO addStaff) {
        //校验员工号
        String staffNumber = addStaff.getStaffNumber();
        Validator.validateNotEmpty(staffNumber, Tip.ERROR_INPUT.content());
        QueryWrapper<Staff> staffWrapper = new QueryWrapper<>();
        staffWrapper.eq("staff_number", staffNumber);
        Staff staff = staffMapper.selectOne(staffWrapper);
        Validator.validateNull(staff, Tip.STAFF_EXIST.content());

        //校验姓名
        Validator.validateNotEmpty(addStaff.getName(), Tip.ERROR_INPUT.content());

        //校验性别
        boolean IsGender = false;
        String gender = addStaff.getGender();
        if (gender.equals(Gender.MALE.gender()) || gender.equals(Gender.FEMALE.gender())) {
            IsGender = true;
        }
        Validator.validateTrue(IsGender, Tip.ERROR_INPUT.content());

        //校验手机
        String phone = addStaff.getPhone();
        String idCard = addStaff.getIdCard();
        Validator.validateNotEmpty(phone, Tip.ERROR_INPUT.content());
        Validator.validateNotEmpty(idCard, Tip.ERROR_INPUT.content());
        Validator.isMatchRegex(Validator.MOBILE.pattern(), addStaff.getPhone());
        Validator.isMatchRegex(Validator.CITIZEN_ID.pattern(), addStaff.getIdCard());

        //校验部门和职务
        String department = addStaff.getDepartmentId();
        String post = addStaff.getPostId();
        Validator.validateNotEmpty(department, Tip.ERROR_INPUT.content());
        Validator.validateNotEmpty(post, Tip.ERROR_INPUT.content());
        //校验部门和职务的匹配关系
        QueryWrapper<DepartmentPost> departmentPostWrapper = new QueryWrapper<>();
        departmentPostWrapper.eq("department_id", department);
        departmentPostWrapper.eq("post_id", post);
        DepartmentPost departmentPost = departmentPostMapper.selectOne(departmentPostWrapper);
        Validator.validateNotNull(departmentPost, Tip.MATCH_UP_ERROR.content());
    }
}
