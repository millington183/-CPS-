package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.Department;
import com.flushbonading.cps.entity.dto.DepartmentDTO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-13
 */
public interface DepartmentService extends IService<Department> {
    /**
     * 得到所有部门
     *
     * @return
     */
    List<DepartmentDTO> getAll();
}
