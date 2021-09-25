package com.flushbonading.cps.service.impl;

import cn.hutool.core.lang.Validator;
import cn.hutool.core.util.PageUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.flushbonading.cps.constant.Tip;
import com.flushbonading.cps.entity.Material;
import com.flushbonading.cps.entity.RespBean;
import com.flushbonading.cps.entity.vo.MaterialVO;
import com.flushbonading.cps.mapper.MaterialMapper;
import com.flushbonading.cps.service.MaterialService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 服务实现类
 * </p>
 *
 * @author zyx
 * @since 2021-06-17
 */
@Service
public class MaterialServiceImpl extends ServiceImpl<MaterialMapper, Material> implements MaterialService {

    @Autowired
    MaterialMapper materialMapper;

    @Override
    public List<MaterialVO> showMaterials(String materialId, Integer page) {
        return materialMapper.showMaterials(materialId, page);
    }

    @Override
    public Integer materialCounts(String materialId) {
        return materialMapper.materialCounts(materialId);
    }

    @Override
    public Integer totalPages(String materialId) {
        return PageUtil.totalPage(materialCounts(materialId), 7);
    }

    @Override
    public RespBean addAMaterial(MaterialVO material) {
        String materialId = material.getMaterialId();
        Double al = material.getAl();
        Double fe = material.getFe();
        Double b = material.getB();
        Validator.validateNotEmpty(materialId, Tip.ERROR_INPUT.content());
        if (al == null || fe == null || b == null) {
            return RespBean.error(Tip.ERROR_INPUT.content());
        }
        if (al.doubleValue() < 0 || al.doubleValue() >= 1) {
            return RespBean.error(Tip.ERROR_INPUT.content());
        }
        if (b.doubleValue() < 0 || b.doubleValue() >= 1) {
            return RespBean.error(Tip.ERROR_INPUT.content());
        }
        if (fe.doubleValue() < 0 || fe.doubleValue() >= 1) {
            return RespBean.error(Tip.ERROR_INPUT.content());
        }

        QueryWrapper<Material> queryWrapper = new QueryWrapper<>();
        queryWrapper.eq("material_id", materialId);
        Material selectMaterial = materialMapper.selectOne(queryWrapper);
        Validator.validateNull(selectMaterial, Tip.MATERIAL_EXIST.content());

        Integer addCount = materialMapper.addAMaterial(material);
        Validator.validateNotNull(addCount, Tip.INSERT_ERROR.content());
        return RespBean.success(Tip.INSERT_SUCCESS.content());
    }

    @Override
    public RespBean deleteAMaterialByMaterialId(String materialId) {
        Integer deleteMaterial = materialMapper.deleteAMaterialByMaterialId(materialId);
        Validator.validateNotNull(deleteMaterial, Tip.DELETE_ERROE.content());
        return RespBean.success(Tip.DELETE_SUCCESS.content());
    }

    @Override
    public RespBean updateAMaterial(MaterialVO material) {
        String materialId = material.getMaterialId();
        Double al = material.getAl();
        Double fe = material.getFe();
        Double b = material.getB();
        Validator.validateNotEmpty(materialId, Tip.ERROR_INPUT.content());
        if (al == null || fe == null || b == null) {
            return RespBean.error(Tip.ERROR_INPUT.content());
        }
        if (al.doubleValue() < 0 || al.doubleValue() >= 1) {
            return RespBean.error(Tip.ERROR_INPUT.content());
        }
        if (b.doubleValue() < 0 || b.doubleValue() >= 1) {
            return RespBean.error(Tip.ERROR_INPUT.content());
        }
        if (fe.doubleValue() < 0 || fe.doubleValue() >= 1) {
            return RespBean.error(Tip.ERROR_INPUT.content());
        }

        Integer updateMaterial = materialMapper.updateAMaterial(material);
        Validator.validateNotNull(updateMaterial, Tip.EDIT_ERROR.content());
        return RespBean.success(Tip.EDIT_SUCCESS.content());
    }

    @Override
    public List<String> getBrandName() {
        return materialMapper.getBrandName();
    }
}
