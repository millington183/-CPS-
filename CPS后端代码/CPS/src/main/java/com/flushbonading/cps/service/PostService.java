package com.flushbonading.cps.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.flushbonading.cps.entity.Post;
import com.flushbonading.cps.entity.dto.PostDTO;

import java.util.List;

/**
 * <p>
 * 服务类
 * </p>
 *
 * @author zyx
 * @since 2021-06-13
 */
public interface PostService extends IService<Post> {
    /**
     * 根据部门查询所有职务
     *
     * @param departmentName
     * @return
     */
    List<PostDTO> getPostByDepartment(String departmentName);
}
