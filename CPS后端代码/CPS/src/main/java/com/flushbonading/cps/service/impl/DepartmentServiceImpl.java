package com.flushbonading.cps.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.entity.Department;
import com.flushbonading.cps.entity.dto.DepartmentDTO;
import com.flushbonading.cps.mapper.DepartmentMapper;
import com.flushbonading.cps.service.DepartmentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-13
 */
@Service
public class DepartmentServiceImpl extends ServiceImpl<DepartmentMapper, Department> implements DepartmentService {

    @Autowired
    DepartmentMapper departmentMapper;
    
    @Override
    public List<DepartmentDTO> getAll() {
        return departmentMapper.getAll();
    }
}
